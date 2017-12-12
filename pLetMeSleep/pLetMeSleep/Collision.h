#pragma once

#include "SDL.h"

class Collider;

class Collision {

public:

	static bool isCollision(const SDL_Rect& rec1, const SDL_Rect& rec2);
	static bool isCollision(const Collider& col1, const Collider& col2);

};