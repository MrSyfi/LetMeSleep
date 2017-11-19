#pragma once
#include "Game.h"
class Map
{
public:

	Map();
	~Map();

	int randomLayout(int max);

	void addMap();

	void loadMap(std::string path);
	void drawMap();

private:

	SDL_Rect srcRect, destRec;

	SDL_Texture* tile;
	SDL_Texture* grass;
	SDL_Texture* floor;
	
	int map[20][20];

};
