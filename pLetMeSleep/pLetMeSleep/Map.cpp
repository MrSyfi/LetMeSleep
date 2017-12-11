#include "Map.h"
#include "TextureManager.h"
#include "Room.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <random>
#include "time.h"

Map::Map() 
{

}

Map::Map(int width, int height)
{

	//Textures of all tile
	tile = TextureManager::LoadTexture("map_texture/tile.jpg");
	desk = TextureManager::LoadTexture("map_texture/desk.jpg");
	wall = TextureManager::LoadTexture("map_texture/wall.jpg");
	doorRight = TextureManager::LoadTexture("map_texture/doorRight.jpg");
	bottomArrow = TextureManager::LoadTexture("map_texture/door.gif");
	doorLeft = TextureManager::LoadTexture("map_texture/doorLeft.jpg");

	loadMap("map_layouts/layout_menu.txt");
	//addMap();
	//Equivalent to src.x = 0 & src.y = 0
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRec.w = width/20;
	srcRect.h = destRec.h = height/20;

	destRec.x = destRec.y = 0;

}


Map::~Map()
{


}

int Map::randomLayout(int max) {
	//Generates a random number to switch between random layouts for the current room

	//srand(time) allows to "seed" the pseudo-randomizer to allow to generate a different number each time
	//without srand(time), the number will always be the same (example : 6 will always give 6, even after being passed in the randomizer)
	srand(time(NULL));
	return std::rand() % max + 1;
	
}

void Map::addMap() {
	loadMap("map_layouts/layout_" + std::to_string(randomLayout(6)) + ".txt");
}

void Map::loadMap(std::string path)
{	//Reads the number inside the file, then adds it to the map
	std::ifstream file(path);
	if (file.is_open()) {
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 20; j++) {
				file >> map[i][j];
			}
		}
	}
}

void Map::drawMap(int width, int height) {

	int type = 0;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {

			type = map[i][j];

			destRec.x = j * width/20;
			destRec.y = i * height/20;
			switch (type) {

			case 0 : 
				TextureManager::draw(tile, srcRect, destRec);
				break;
			case 1 :
				TextureManager::draw(desk, srcRect, destRec);
				break;
			case 2 :
				TextureManager::draw(wall, srcRect, destRec);
				break;
			case 3:
				TextureManager::draw(doorRight, srcRect, destRec);
				break;
			case 4:
				TextureManager::draw(bottomArrow, srcRect, destRec);
				break;
			case 5:
				TextureManager::draw(doorLeft, srcRect, destRec);
			default :
				break;

			}


		}

	}

}
