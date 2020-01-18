#include "sprite.h"

sprite::sprite(const sf::Vector2f & size) : RectangleShape(size)
{
}

sprite::~sprite()
{
}

void sprite::setVelocity(sf::Vector2f vel)
{
	velocity = vel; 
}

void sprite::setVelocity(float vx, float vy)
{
	velocity.x = vx; 
	velocity.y = vy;
}

sf::Vector2f sprite::getVelcity()
{
	return velocity;
}

sf::FloatRect sprite::getAABB()
{
	return AABB;
}

void sprite::updateAABB()
{
	// Axis Aligned Bounding Box, based on sprite size and position.
	// Shape could be smaller/larger and offset if required.
	// Can be overwritten by child classes
	//AABB.left = getPosition().x;
	//AABB.top = getPosition().y;
	//AABB.width = getSize().x;
	//AABB.height = getSize().y;
}

void sprite::collisionRespone()
{
	// e.g. compare sprite positions to determine new velocity direction.
	// e.g. checking sprite type (world, enemy, bullet etc) so response is based on
	//that.
}