#pragma once

#include "SDL.h"
#include "ECSystem.h"
#include "Components.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:

	TransformComponent *transform;
	SDL_Texture *text;
	SDL_Rect srcRect, destRect;

public:
	

	SpriteComponent() = default;
	SpriteComponent(const char* path) {

		setText(path);

	}

	~SpriteComponent() {

		SDL_DestroyTexture(text);

	}

	void setText(const char* path) {

		text = TextureManager::LoadTexture(path);

	}

	void init() override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		destRect.w = destRect.h = 64;

	}

	void update() override {

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width*transform->scale;
		destRect.h = transform->height*transform->scale;

	}

	void draw() override {

		TextureManager::draw(text, srcRect, destRect);

	}


};

