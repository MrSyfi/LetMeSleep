#pragma once
#include "Game.h"
class GameObject
{
public:
	GameObject();
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();
	// Update is virtual, like that, an update method is applicable for each sort of GameObject.
	virtual void update() = 0;

	
	void drawGameObject();
	bool collision(SDL_Rect tmpRect);
	SDL_Rect getRect() { return destRect; }
	int getX() { return xpos; }
	int getY() { return ypos; }
	int getW() { return destRect.w; }
	int getH() { return destRect.h; }
	
private:
	
	
	SDL_Texture* entTexture;

protected:
	// Every GameObject has a src and destRect and a position
	
	int xpos, ypos;
	SDL_Rect srcRect;
	SDL_Rect destRect;

};


