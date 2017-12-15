#pragma once

#include "ECSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class Tile : public Component {

public : 
	
	TransformComponent *transform;
	SpriteComponent *sprite;

	SDL_Rect rect;
	int id;
	char* path;

	Tile() = default;

	Tile(int id, int x, int y, int w, int h) {

		this->id = id;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		switch (this->id)
		{
		case 0 :
			path = "map_texture/tile.jpg";
			break;

		case 1:
			path = "map_texture/desk.jpg";
			break;

		case 2 : 
			path = "map_texture/wall.jpg";
			break;

		case 3 :
			path = "map_texture/doorRight.jpg";
			break;

		case 4 : 
			path = "map_texture/door.gif";
			break;

		case 5 : 
			path = "map_texture/doorLeft.jpg";
			break;

		default:
			break;
		}

	}

	void init() override {

		entity->addComponent<TransformComponent>(rect.x, rect.y, rect.w, rect.y, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();


	}

};