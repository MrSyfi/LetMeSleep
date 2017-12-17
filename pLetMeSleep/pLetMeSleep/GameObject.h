#pragma once
#include "Game.h"
class GameObject
{
public:
	GameObject();
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();
	// Update is virtual, like that, an update method is applicable for each sort of GameObject.
	virtual void update(int i) = 0;

	
	void drawGameObject();
	bool collision(SDL_Rect tmpRect);
	SDL_Rect getRect() { return destRect; }
	int getX() const { return xpos; }
	int getY() const { return ypos; }
	void setX(int x) { xpos = x; }
	void setY(int y) { ypos = y; }
	int getW() const { return destRect.w; }
	int getH() const { return destRect.h; }

	GameObject(const GameObject &g);
	GameObject& operator=(const GameObject &g);

	
private:
	
	SDL_Texture* entTexture;

protected:
	// Every GameObject has a src and destRect and a position
	
	int xpos, ypos;
	SDL_Rect srcRect;
	SDL_Rect destRect;

};


