#pragma once

#include <string>
#include "SDL.h"
#include "Components.h"


class Collider : public Component
{
public:
	SDL_Rect collider;
	//return the name of the object collided
	std::string tag;

	TransformComponent* transform;

	Collider(std::string t) {

		tag = t;

	}

	void init() override {

		if (!entity->hasComponent<TransformComponent>()) {

			entity->addComponent<TransformComponent>();

		}

		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);

	}

	void update() override {

		//Cast float in int
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;

	}

};

