#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "Input.h"

class Player : public Sprite
{
public:
	Player(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Player();

	void update(float dt);
	void movement(float dt, Input input);
	void collisionResponse(float posX, float posY);
	void collisionBounds();

	int getPlayerID();
	void setPlayerID(int playerID);

private:	
	int id; 
	sf::Vector2f velocity; 
	float scale; 
};

