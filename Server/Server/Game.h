#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "Ball.h"

class Game
{
public:
	Game();
	~Game();

	void update(float dt);
	float getBallX(int i);
	float getBallY(int i);

private: 
	Ball balls[5];
	//Ball ball;
};

