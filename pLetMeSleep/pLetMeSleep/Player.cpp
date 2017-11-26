#include "Player.h"
#include <iostream>
#include "SDL_timer.h"


using namespace std;

Player::Player()
{
}

Player::Player(const char * textureSheet, int x, int y) : Actor(textureSheet,x,y)
{
	t0 = 0;
	isCollided = false;
	this->setHealth(100);
	this->setMaxHealth(100);
}

void Player::update(int defense)
{

	int tmp = 32;
	//Manages the collision with the limits of the screen
	if (xpos <1) {
		xpos = 1;
		//dx = -dx;
	}
	else if (xpos > 640 - tmp) {
		xpos = 640 - tmp;
		//dx = -dx;
	}
	else if (ypos < 1) {
		ypos = 1;
		//dy = -dy;
	}
	else if (ypos > 640 - tmp) {
		ypos = 640 - tmp;
		//dy = -dy;
	}
	//Uses dx and dy to move the object



	xpos += dx * 2;
	ypos += dy * 2;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = srcRect.w * 2;
		destRect.h = srcRect.h * 2;

		//Call the isInvulnerable function to check if the invicibility frame is off or not
		isInvulnerable();

		//If there is no invincibility, the player can be damaged 


		if (!invicibility) {
			if (isCollided) {
				int tmp = getHealth();
				std::cout << "Player lost " << defense << "HP" << std::endl;
				this->setHealth(tmp - defense);
				isCollided = false;
				//Gives invicibility frame to the player after getting hit, and sets the timer to the current one
				invicibility = true;
				t0 = SDL_GetTicks();
			}
		
		
	}

}

bool Player::isColl() 
{
	return isCollided;
}
void Player::isInvulnerable() {
	//Will check if the invincibility frame for the player is still on or not, and change the value in consequence
	long delta = SDL_GetTicks()-t0;
	//The invicibility frame is currently one second
	if (delta >= 1000) {
		invicibility = false;
	}
	else {
		invicibility = true;
	}
	
}

void Player::newRoom() {
	invicibility = true;
}

void Player::collideWith(Monster* m)
{

	SDL_Rect* src_p = new SDL_Rect(this->destRect);
	SDL_Rect* src_m = new SDL_Rect(m->getRect());
	isCollided = collision(src_p->x, src_p->y, src_p->w, src_p->h, src_m->x, src_m->y, src_m->w, src_m->h);
	
}

void Player::collideWith(Boss* b) {
	SDL_Rect* src_p = new SDL_Rect(this->destRect);
	SDL_Rect* src_m = new SDL_Rect(b->getRect());
	isCollided = collision(src_p->x, src_p->y, src_p->w, src_p->h, src_m->x, src_m->y, src_m->w, src_m->h);
}

bool Player::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	//Returns true if there is a collision between the player and any monster
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





Player::~Player()
{
}
