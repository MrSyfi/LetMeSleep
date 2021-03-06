#include "Monster.h"
#include "time.h"
#include <iostream>
#include "time.h"
Monster::Monster()
{
}

Monster::Monster(const char * textureSheet, int x, int y) : Actor(textureSheet, x, y)
{
	t0 = 0;
	isCollided = false;
	this->setHealth(12);
}

Monster::Monster(const Monster& a) : Actor(a)
{
	t0 = 0,
	isCollided = false;
	this->setHealth(12);
}

Monster & Monster::operator=(const Monster & a)
{
	if (&a != this) {
		Actor::operator=(a);
		this->t0 = 0;
		this->isCollided = false;
		this->setHealth(12);
	}
	return *this;
}

void Monster::update(int weakness)
{
	srand(time(NULL));
	int random = std::rand() % 4 + 1;
	
	
	if (random == 1 | random == 2 || random == 3) {
		xpos += dx;
		ypos += dy;
	}

	srcRect.h = srcRect.w = 32;
	srcRect.x = srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

	//We call the isInvulnerable() method to check if the monster
	// or the boss can be damaged again
	isInvulnerable();

	if (!invincibility) {
		if (isCollided) {
			std::cout << "Enemy lost " << weakness << "HP" << std::endl;
			int temp = getHealth();
			this->setHealth(temp - weakness);
			isCollided = false;
			//Gives invicibility frame to the monster after getting hit, and sets the timer to the current one
			invincibility = true;
			t0 = SDL_GetTicks();
		}


	}
}


void Monster::pathFinding(Player * p) {
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

Monster::~Monster()
{
}

void Monster::bombHit() {
	int tmp = getHealth();
	this->setHealth(tmp - 2);
}

void Monster::collideWith(Attack * a)
{

	SDL_Rect* src_p = new SDL_Rect(this->destRect);
	SDL_Rect* src_a = new SDL_Rect(a->getRect());
	isCollided = collision(src_p->x, src_p->y, src_p->w, src_p->h, src_a->x, src_a->y, src_a->w, src_a->h);

}

bool Monster::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
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


void Monster::isInvulnerable() {
	//Will check if the invincibility frame for the monster is still on or not, and change the value in consequence
	long delta = SDL_GetTicks() - t0;
	//The invicibility frame is currently 0.4s
	if (delta >= 400) invincibility = false;
	else invincibility = true;
	

}