#pragma once
#include <SFML\Graphics.hpp>
#include "sprite.h"

class Ball : public sprite
{
public:
	Ball(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Ball();

	void update(float dt);
	void movement(float dt);
	void collisionResponse(sprite* sp);
	void collisionBounds();
	void setVelocity(float vx, float vy); 

private: 
	sf::Vector2f velocity; 
	float scale; 
};

