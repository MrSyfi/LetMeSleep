#pragma once

#include "SDL.h"
#include "ECSystem.h"
#include "Components.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:

	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

public:
	

	SpriteComponent() = default;
	SpriteComponent(const char* path) {

		texture = TextureManager::LoadTexture(path);

	}

	void setTex(const char* path) {

		texture = TextureManager::LoadTexture(path);

	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		destRect.w = destRect.h = 64;

	}

	void update() override {

		destRect.x = transform->position.x;
		destRect.y = transform->position.y;

	}

	void draw() override {

		TextureManager::draw(texture, srcRect, destRect);

	}


};

