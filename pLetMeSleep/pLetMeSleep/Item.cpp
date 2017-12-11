#include "Item.h"



Item::Item()
{
}



Item::Item(const char * textureSheet, int x, int y, bool isActive) : GameObject(textureSheet, x, y)
{
	srand(time(NULL));
	this->isActive = isActive;
	createItem();
}





Item::~Item()
{
}


void Item::update(int i)
{

	srcRect.h = 16;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;


	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}
void Item::createItem() {
	//The behavior of the item will be different, depending if it is an activable or not
	if (!isActive) {
		int rand = std::rand() % 2 + 1;

		if (rand == 1) {
			defense = true;
		}
		else {
			defense = false;
		}
	}
}

bool Item::isColl() {
	return isCollided;
}

bool Item::isActi() {
	return isActive;
}

bool Item::isDefense() {
	return defense;
}

void Item::collideWith(Player* p)
{

	SDL_Rect* src_p = new SDL_Rect(this->destRect);
	SDL_Rect* src_a = new SDL_Rect(p->getRect());
	isCollided = collision(src_p->x, src_p->y, src_p->w, src_p->h, src_a->x, src_a->y, src_a->w, src_a->h);
}

bool Item::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	//Returns true if there is a collision between the item and the player
	if (x1 <= x2) {
		if (x1 + w1 > x2) {
			return (((y1 < y2) && (y1 + h1 > y2)) ||
				((y1 > y2) && (y2 + h2 > y1)) ||
				(y1 == y2));
		}
	}
	else {
		return collision(x2, y2, w2, h2, x1, y1, w1, h1);
	}
	return false;
}