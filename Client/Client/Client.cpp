#include <iostream>
#include <string>
#include <SFML/Network.hpp>

//Includes
#include "Game.h"

using namespace std;

//IP 
#define SERVERIP "127.0.0.1"

//TCP Port number
#define SERVERPORT 5555

sf::TcpSocket socket; 

void main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Client");
	Input input; 

	sf::Clock timer; 
	sf::Clock clock; 
	float deltaTime; 
	float time; 
	float startTime; 

	//Connect to server 
	socket.connect(SERVERIP, SERVERPORT);

	Game game(&window, &socket, &startTime);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0,
					event.size.width, event.size.height)));
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeftDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRightDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		//DeltaTime 
		deltaTime = clock.restart().asSeconds();
		time = timer.getElapsedTime().asMilliseconds();

		//Game state
		game.handleInput(deltaTime, input);
		game.update(time, &timer, deltaTime, &socket);
		game.render();
	}
}