#include "Collision.h"
#include "Collider.h"

bool Collision::isCollision(const SDL_Rect& rec1, const SDL_Rect& rec2) {

	if (rec1.x + rec1.w >= rec2.x && rec2.x + rec2.w >= rec1.x && 
		rec1.y + rec1.h >= rec2.y && rec2.y + rec2.h >= rec1.y) {

		return true;

	}

	return false;

}

bool Collision::isCollision(const Collider& col1, const Collider& col2) {

	if (isCollision(col1.collider, col2.collider)) {

		std::cout << col1.tag << " hit " << col2.tag << std::endl;
		return true;

	}
	return false;

}