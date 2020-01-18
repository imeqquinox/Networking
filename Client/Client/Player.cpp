#include "Player.h"

Player::Player(const sf::Vector2f & size)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(100, 100);
	setFillColor(sf::Color::Red);

	scale = 200.f; 
}

Player::~Player()
{
}

void Player::update(float dt)
{
}

void Player::movement(float dt, Input input)
{
	if (input.isKeyDown(sf::Keyboard::D))
	{
		velocity.x = 2.0f * scale; 
		move(velocity.x * dt, 0);
	}
	
	if (input.isKeyDown(sf::Keyboard::A))
	{
		velocity.x = -2.0f * scale;
		move(velocity.x * dt, 0);
	}
	
	if (input.isKeyDown(sf::Keyboard::W))
	{
		velocity.y = -2.0f * scale; 
		move(0, velocity.y * dt);
	}
	
	if (input.isKeyDown(sf::Keyboard::S))
	{
		velocity.y = 2.0f * scale;
		move(0, velocity.y * dt);
	}
}

void Player::collisionBounds()
{
	//Right Wall
	if (getPosition().x >= 800 - getSize().x)
	{
		setPosition(800 - getSize().x, getPosition().y);
	}

	//Left Wall
	if (getPosition().x <= 0)
	{
		setPosition(0, getPosition().y);
	}

	//Top Wall
	if (getPosition().y <= 0)
	{
		setPosition(getPosition().x, 0);
	}

	//Bottom Wall
	if (getPosition().y >= 600 - getSize().y)
	{
		setPosition(getPosition().x, 600 - getSize().y);
	}
}

void Player::collisionResponse(float posX, float posY)
{
	//Checks if the player is either to the left/right or above/below the tile
	if (abs(getPosition().x - posX) > abs(getPosition().y - posY))
	{
		//Checks if the player is to the right or left of the tile and stops them from overlapping the tile
		if (getPosition().x <= posX + 50 && getPosition().x > posX + (50 / 2))
		{
			velocity.x = 0;
			setPosition(posX + 50, getPosition().y);
		}
		else
		{
			velocity.x = 0;
			setPosition(posX - getSize().x, getPosition().y);
		}
	}
	else
	{
		//Checks if the player is above or below the tile and stops them from overlapping the tile. 
		if (getPosition().y >= posY - getSize().y && getPosition().y < posY + (50 / 2))
		{
			velocity.y = 0;
			velocity.x = 0;
			setPosition(getPosition().x, posY - getSize().y);
		}
		else
		{
			velocity.x = 0;
			setPosition(getPosition().x, posY + 50);
		}
	}
}

int Player::getPlayerID()
{
	return id;
}

void Player::setPlayerID(int playerID)
{
	id = playerID;
}

/*/Checks if the player is either to the left/right or above/below the tile
	if (abs(getPosition().x - sp->getPosition().x) > abs(getPosition().y - sp->getPosition().y))
	{
		//Checks if the player is to the right or left of the tile and stops them from overlapping the tile
		if (getPosition().x <= sp->getPosition().x + sp->getSize().x && getPosition().x > sp->getPosition().x + (sp->getSize().x / 2))
		{
			velocity.x = 0;
			setPosition(sp->getPosition().x + sp->getSize().x, getPosition().y);
		}
		else
		{
			velocity.x = 0;
			setPosition(sp->getPosition().x - getSize().x, getPosition().y);
		}
	}
	else
	{
		//Checks if the player is above or below the tile and stops them from overlapping the tile.
		if (getPosition().y >= sp->getPosition().y - getSize().y && getPosition().y < sp->getPosition().y + (sp->getSize().y / 2))
		{
			velocity.y = 0;
			velocity.x = 0;
			setPosition(getPosition().x, sp->getPosition().y - getSize().y);
		}
		else
		{
			velocity.x = 0;
			setPosition(getPosition().x, sp->getPosition().y + sp->getSize().y);
		}
	}*/