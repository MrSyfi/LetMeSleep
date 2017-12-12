#pragma once

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {

public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;
	int speed = 3;


	TransformComponent() {

		position.reset();

	}

	TransformComponent(int sc) {

		position.reset();
		scale = sc;

	}

	TransformComponent(float x, float y) {

		position.x = x;
		position.y = y;

	}

	TransformComponent(float x, float y, int h, int w, int s) {

		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = s;

	}

	void init() override {

		velocity.reset();

	}

	void update() override {

		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

	}

};
