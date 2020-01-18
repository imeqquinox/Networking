#include "Game.h"

Game::Game(sf::RenderWindow* hwnd, sf::TcpSocket* socket, float* startTime)
{
	window = hwnd;

	//Generate a random playerID between 0 and 10000
	srand(time(NULL));
	int num = rand() % 10000;
	player.setPlayerID(num);

	//Init other player
	otherPlayer.setSize(sf::Vector2f(50, 50));
	otherPlayer.setFillColor(sf::Color::Blue);

	//Init balls 
	for (int i = 0; i < 5; i++)
	{
		circle[i].setRadius(25);
		circle[i].setPosition(250, 250);
		circle[i].setFillColor(sf::Color::Green);
	}
	
	//Recieve data for the server to calculate the median game time used for this player
	for (int i = 0; i < 5; i++)
	{
		if (socket->receive(packet) == sf::Socket::Done)
		{
			packet >> msg;
		}

		packet << msg; 
		socket->send(packet);
		packet.clear();
	}

	//Send player ID
	packet << player.getPlayerID();
	socket->send(packet);
	packet.clear();
}

Game::~Game()
{
}

void Game::update(float time, sf::Clock* timer, float dt, sf::TcpSocket* socket)
{	
	//Every 30 ms send game data 
	if (time >= 30)
	{
		//Only send 40 packets 
		//if ((rand() % 100) > 40)
		//{
			//Send player data 
			packet << player.getPlayerID() << player.getPosition().x << player.getPosition().y;
			socket->send(packet);
			packet.clear();
		//}

		timer->restart().asMilliseconds();
	}

	//Recieve balls 
	socket->receive(packet);
	float cX[5], cY[5];
	packet >> cX[0] >> cX[1] >> cX[2] >> cX[3] >> cX[4]
		>> cY[0] >> cY[1] >> cY[2] >> cY[3] >> cY[4];
	for (int i = 0; i < 5; i++)
	{
		circle[i].setPosition(cX[i], cY[i]);
	}

	//Recieve other player position by checking the player ID to make sure it's not our own.
	float x[2], y[2];
	int playID[2];
	packet >> playID[0] >> playID[1]
		>> x[0] >> x[1]
		>> y[0] >> y[1];
	for (int i = 0; i < 2; i++)
	{
		if (playID[i] != player.getPlayerID())
		{
			otherPlayer.setPosition(x[i], y[i]);
		}
	}
	packet.clear();

	//Player bounds against the screen screen 
	player.collisionBounds();
}

void Game::handleInput(float dt, Input input)
{
	//Player movement 
	player.movement(dt, input);
}

void Game::render()
{

	beginDraw();
	for (int i = 0; i < 5; i++)
	{
		window->draw(circle[i]);
	}

	window->draw(otherPlayer);

	window->draw(player);
	endDraw();
}

void Game::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Game::endDraw()
{
	window->display();
}

