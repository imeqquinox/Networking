#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Input.h"
#include "Player.h"

class Game 
{
public:
	Game(sf::RenderWindow* hwnd, sf::TcpSocket* socket, float* startTime);
	~Game();
	void handleInput(float dt, Input input);
	void update(float time, sf::Clock* timer, float dt, sf::TcpSocket* socket);
	void render();

private:
	sf::RenderWindow* window;
	void beginDraw();
	void endDraw();

	Player player; 
	sf::RectangleShape otherPlayer;
	sf::CircleShape circle[5];

	//Network variables 
	sf::Packet packet;
	std::string msg; 
};

