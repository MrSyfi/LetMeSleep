#include "Container.h"



Container::Container()
{
}

Container::Container(const char * textureSheet, int x, int y, int modx, int mody) :GameObject(textureSheet,x,y)
{
	this->modx = modx;
	this->mody = mody;
}


Container::~Container()
{
}


void Container::update(int i)
{
	//As containers can have different sizes, we use the mody and modx value we received in the constructor
	srcRect.h = mody;
	srcRect.w = modx;
	srcRect.x = 0;
	srcRect.y = 0;


	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}
