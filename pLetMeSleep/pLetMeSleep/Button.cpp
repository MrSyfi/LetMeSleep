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

Button::Button(const Button& a) : Actor(a)
{

}

Button & Button::operator=(const Button & a)
{
	if (&a != this) {
		Actor::operator=(a);
	}
	return *this;
}

bool Button::isOnTop(int mouseX, int mouseY)
{
	//Checks if the mouse is on top of the button when the mouseclick has been pressed
	if (mouseX >= getX() && mouseX <= getX() + getW() && mouseY >= getY() && mouseY <= getY() + getH()) {
		return true;
	}
	//If it is not, return false
	return false;
}






void Button::update(int i)
{
	//All the buttons have the same size
	srcRect.h = 64;
	srcRect.w = 128;
	srcRect.x = 0;
	srcRect.y = 0;


	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}