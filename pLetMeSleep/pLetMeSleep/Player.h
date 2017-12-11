#pragma once
#include "Actor.h"
#include "Monster.h"
#include "Attack.h"
#include "Boss.h"
#include <vector>
using std::vector;
class Monster;
class Boss;

class Player :
	public Actor
{
public:
	Player();
	Player(const char* textureSheet, int x, int y);
	void update(int defense);
	bool canActi();
	void setActi(bool value);
	bool isColl();
	//void update() override;
	void isInvulnerable();
	void newRoom();
	void collideWith(Monster* m);
	void collideWith(Boss* b);
	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	~Player();
private:
	//Contains all the different attack the player did
	vector<Attack> attacks;
	// Rectangle before each movement;
	SDL_Rect tmpRect;
	bool isCollided;
	//Sets a delay between each attack;
	int t0;
	bool invicibility;

	//Defines if the player can use the activable item he has or not
	bool canUseActivable = false;
};

