#include "Game.h"

Game::Game()
{
	srand(time(NULL));
	float ranVel[5];
	for (int i = 0; i < 5; i++)
	{
		ranVel[i] = rand() % 25 - 5;
	}

	for (int i = 0; i < 5; i++)
	{
		balls[i].setVelocity(ranVel[i], ranVel[i]);
	}
}

Game::~Game()
{
}

void Game::update(float dt)
{
	for (int i = 0; i < 5; i++)
	{
		balls[i].movement(dt);
		balls[i].collisionBounds();
	}
}

float Game::getBallX(int i)
{
	return balls[i].getPosition().x;
}

float Game::getBallY(int i)
{
	return balls[i].getPosition().y;
}
