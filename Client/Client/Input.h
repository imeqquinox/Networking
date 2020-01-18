#pragma once

class Input
{
private:
	bool keys[256]{ false };
	struct Mouse
	{
		int x, y;
		bool left;
		bool right;
	};
	Mouse mouse;

public:
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

	void setMousePosition(int x, int y);
	void setMouseLeftDown(bool);
	void setMouseRightDown(bool);
	bool getMouseLeft();
	bool getMouseRight();
	int getMouseX();
	int getMouseY();
};

