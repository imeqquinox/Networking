#include <iostream>
#include <string>
#include <list>
#include "SFML/Network.hpp"
#include "Game.h"

using namespace std; 
using namespace sf; 

//IP
#define SERVERIP "127.0.0.1"

//TCP Port number 
#define SERVERPORT 5555

int main()
{
	Game game;

	//Player Variables 
	struct Player
	{
		int playerID;
		float currentX, currentY;
		float lastX, lastY;
		float currentTime;
		float lastTime; 
		float medianTime; 
	};
	Player players[2];
	float startTime[2];
	float velocity[3];
	int i = 0; 

	Clock clock;
	Clock gameClock;
	Clock timer; 
	float deltaTime;
	float gameTime; 
	float times[5];

	float newPosX;
	float newPosY;

	//Create a socket to listen to a new connections 
	TcpListener listener;
	listener.listen(SERVERPORT);

	//Create a list to store the future clients 
	list<TcpSocket*> clients;

	//Create a selector
	SocketSelector selector;
	//Add the listner to the selector 
	selector.add(listener);

	printf("Waiting for a connection...\n");

	//Waiting lobby for 2 minimum of 2 players 
	while (i < 2)
	{
		if (selector.wait(microseconds(1)))
		{
			if (selector.isReady(listener))
			{
				TcpSocket* client = new TcpSocket;
				if (listener.accept(*client) == Socket::Done)
				{
					printf("Connected\n");
					//Add the new client to the clients list 
					clients.push_back(client);

					//Add the new client to the selector so that we will
					//be notified when the socket sends something 
					selector.add(*client);

					//Send a packet to each player to calculate the time for sending to the player
					//Do this 5 times for the median 
					Packet packet;
					for (int i = 0; i < 5; i++)
					{
						timer.restart().asMicroseconds();

						packet << "Hello"; 
						client->send(packet);
						packet.clear();
						
						if (client->receive(packet) == Socket::Done)
						{
							string msg; 
							packet >> msg; 
							packet.clear();

							times[i] = (timer.getElapsedTime().asMilliseconds() / 2);
						}
					}
					
					//Find the median time for each players game timer 
					sort(times, times + 5);
					players[i].medianTime = times[3];
					startTime[i] = players[i].medianTime;

					//Recieve player ID data 
					if (client->receive(packet) == Socket::Done)
					{
						int my_id;
						packet >> my_id;

						players[i].playerID = my_id;
						i++;
					}
				}
			}
		}
	}

	//Restart game clock for game starting 
	gameClock.restart().asMilliseconds();

	//Endless server loop
	while (true)
	{
		gameTime = gameClock.getElapsedTime().asMilliseconds();
		deltaTime = clock.restart().asSeconds();

		game.update(deltaTime);

		//Make the selector wait for data on any socket 
		if (selector.wait(microseconds(1000)))
		{
			//The listener socket is not ready, test all the other sockets (the clients)
			for (list<TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
			{
				TcpSocket& client = **it;
				if (selector.isReady(client))
				{
					Packet packet;
					//The client has sent some data, we can recieve it 
					if (client.receive(packet) == Socket::Done)
					{
						int my_id;
						packet >> my_id;

						for (int i = 0; i < 2; i++)
						{
							if (my_id == players[i].playerID)
							{
								float x, y;
								packet >> x >> y;

								//Pass preious values into back arrays (for prediction)
								//Output current players position
								players[i].lastX = players[i].currentX;
								players[i].lastY = players[i].currentY;

								players[i].currentX = x;
								players[i].currentY = y;
								cout << "PlayerID: " << players[i].playerID << endl;
								cout << "Player x position: " << players[i].currentX << endl;
								cout << "Player y position: " << players[i].currentY << endl;
								cout << endl;
								packet.clear();
								
								//Push back on gametime array for each player
								//Output current time for each
								players[i].lastTime = players[i].currentTime;
								players[i].currentTime = gameTime - startTime[i];
								cout << "Game Time: " << players[i].currentTime << endl;
								cout << endl; 
								packet.clear();

								break;
							}
						}
					}
				}
			}
		}
		else
		{
			//Not received a packet in time
			//Do prediction 
			//Interpolation between predicted position and actual position
			for (int i = 0; i < 2; i++)
			{
				//Calculate the difference between last 2 packets 
				float distX = (players[i].currentX + players[i].lastX);
				float distY = (players[i].currentY + players[i].lastY);
				float time = (players[i].currentTime + players[i].lastX);

				//Calculate velocity 
				float velocityX = distX / time;
				float velocityY = distY / time;

				//new position used for interpolation 
				//newPosX = (players[i].currentX + velocityX);
				//newPosY = (players[i].currentY + velocityY);
				players[i].currentX + velocityX;
				players[i].currentY + velocityY;

				//Interpolate between 0 and 1 
				//for (int j = 0; j < 1; j += 0.1)
				//{
					//players[i].currentX += j * (newPosX - players[i].currentX);
					//players[i].currentY += j * (newPosY - players[i].currentY);
				//}
			}
		}

		for (list<TcpSocket*>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			//Send the players data of the other player and where the balls are 
			TcpSocket& client = **it;
			Packet packet;

			for (int i = 0; i < 5; i++)
			{
				packet << game.getBallX(i) << game.getBallY(i);
			}

			packet << players[0].playerID << players[1].playerID
				<< players[0].currentX << players[1].currentX
				<< players[0].currentY << players[1].currentY; 
				
			client.send(packet);
			packet.clear();
		}
	}

	return 0;
}

