#include "Boss.h"
#include "time.h"
#include <iostream>
#include "time.h"
Boss::Boss()
{
}

Boss::Boss(const char * textureSheet, int x, int y) : Actor(textureSheet, x, y)
{
	t0 = 0;
	isCollided = false;
	this->setHealth(40);
}
Boss::Boss(const Boss& a) : Actor(a)
{
	this->t0 = 0;
	this->isCollided = 0;
	this->setHealth(40);
}

Boss & Boss::operator=(const Boss & a)
{
	if (&a != this) {
		Actor::operator=(a);
		this->t0 = 0;
		this->isCollided = 0;
		this->setHealth(40);
	}
	return *this;
}



void Boss::update(int weakness)
{
	//The boss will go as fast as the player, so we multiply the velocity values by 2
xpos += dx*2;
		ypos += dy*2;

	srcRect.h = srcRect.w = 128;
	srcRect.x = srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

	//Checks if the entity can be attacked again or not
	isInvulnerable();
	if (!invincibility) {
		if (isCollided) {
			int temp = getHealth();
			this->setHealth(temp - weakness);
			isCollided = false;
			//Gives invicibility frame to the monster after getting hit, and sets the timer to the current one
			invincibility = true;
			t0 = SDL_GetTicks();
		}


	}
}


void Boss::pathFinding(Player * p) {


	//Number of pixels between the x and y positions of the monster and the player
	int diffx = xpos - p->getX();
	int diffy = ypos - p->getY();

	srand(time(NULL));
	int random = std::rand() % 2 + 1;
	// Allows to change either x or y at random
	if (random == 1) {
		// Changes the value of move() following the different values
		if (diffx > 0) {
			this->move(2);
		}
		else if (diffx < 0) {
			this->move(3);

		}
		else if (diffy > 0) {
			this->move(0);

		}
		else if (diffy < 0) {
			this->move(1);

		}
	}
	else {
		if (diffy > 0) {
			this->move(0);

		}
		else if (diffy < 0) {
			this->move(1);

		}
		else if (diffx > 0) {
			this->move(2);

		}
		else if (diffx < 3) {
			this->move(1);

		}


	}
}

Boss::~Boss()
{
}

void Boss::collideWith(Attack * a)
{

	SDL_Rect* src_p = new SDL_Rect(this->destRect);
	SDL_Rect* src_a = new SDL_Rect(a->getRect());
	isCollided = collision(src_p->x, src_p->y, src_p->w, src_p->h, src_a->x, src_a->y, src_a->w, src_a->h);

}

bool Boss::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	//Returns true if there is a collision between the monster and any attack from the player
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


void Boss::isInvulnerable() {
	//Will check if the invincibility frame for the monster is still on or not, and change the value in consequence
	long delta = SDL_GetTicks() - t0;
	//The invicibility frame is currently 0.4s
	if (delta >= 400) {
		invincibility = false;
	}
	else {
		invincibility = true;
	}

}