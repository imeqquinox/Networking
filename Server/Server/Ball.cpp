#include "Ball.h"

Ball::Ball(const sf::Vector2f & size)
{
	setSize(sf::Vector2f(25, 25));
	setPosition(250, 250);
	setFillColor(sf::Color::Green);

	scale = 50.f;

	velocity.x = 2.0f * scale;
	velocity.y = 2.0f * scale;
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{

}

void Ball::movement(float dt)
{
	move(velocity.x * dt, velocity.y * dt);
}

void Ball::collisionBounds()
{
	//Right Wall
	if (getPosition().x >= 800 - getSize().x)
	{
		velocity.x = -rand() % 25 * scale; 
	}

	//Left Wall
	if (getPosition().x <= 0)
	{
		velocity.x = rand() % 25 * scale;
	}

	//Top Wall
	if (getPosition().y <= 0)
	{
		velocity.y = rand() % 25 * scale;
	}

	//Bottom Wall
	if (getPosition().y >= 600 - getSize().y)
	{
		velocity.y = -rand() % 25 * scale;
	}
}

void Ball::setVelocity(float vx, float vy)
{
	velocity.x = vx * scale; 
	velocity.y = vy * scale; 
}
