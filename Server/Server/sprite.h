#pragma once
#include "SFML\Graphics.hpp"

class sprite : public sf::RectangleShape
{
public:
	sprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~sprite();

	virtual void update(float dt) = 0;
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelcity();

	sf::FloatRect getAABB();
	virtual void updateAABB();
	virtual void collisionRespone();
	void setAlive(bool live) { alive = live; };
	bool isAlive() { return alive; };

protected: 
	bool alive; 
	sf::Vector2f velocity; 
	sf::FloatRect AABB;
};

