#include "Button.h"



Button::Button(const char * textureSheet, int x, int y) : Actor(textureSheet,x,y)
{
}

Button::Button()
{
}


Button::~Button()
{
}

bool Button::isOnTop(int mouseX, int mouseY)
{
	//Checks if the mouse is on top of the button when the mouseclick has been pressed
	if (mouseX >= getX() && mouseX <= getX() + getW() && mouseY >= getY() && mouseY <= getY() + getH()) {
		return true;
	}
	return false;
}

void Button::update()
{
	srcRect.h = 64;
	srcRect.w = 128;
	srcRect.x = 0;
	srcRect.y = 0;


	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}