#pragma once
#include "Game.h"
class Map
{
public:

	Map();
	Map(int width, int height);
	~Map();

	int randomLayout(int max);

	void addMap();

	void loadMap(std::string path);
	void drawMap(int width, int height);
	//void drawMap();

private:

	SDL_Rect srcRect, destRec;

	SDL_Texture* tile;
	SDL_Texture* grass;
	SDL_Texture* floor;
	SDL_Texture* doorRight;
	SDL_Texture* bottomArrow;
	SDL_Texture* doorLeft;
	
	int map[20][20];

};

