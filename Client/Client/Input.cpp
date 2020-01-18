#include"Input.h"

void Input::setKeyDown(int key)
{
	keys[key] = true;
}

void Input::setKeyUp(int key)
{
	keys[key] = false;
}

bool Input::isKeyDown(int key)
{
	return keys[key];
}

void Input::setMousePosition(int x, int y)
{
	mouse.x = x;
	mouse.y = y;
}

void Input::setMouseLeftDown(bool input)
{
	mouse.left = input;
}

void Input::setMouseRightDown(bool input)
{
	mouse.right = input;
}

int Input::getMouseX()
{
	return mouse.x;
}

int Input::getMouseY()
{
	return mouse.y;
}

bool Input::getMouseLeft()
{
	return mouse.left;
}

bool Input::getMouseRight()
{
	return mouse.right;
}
