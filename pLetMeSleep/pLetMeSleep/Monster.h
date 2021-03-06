#pragma once
#include "Actor.h"
#include "Player.h"
#include "Attack.h"
#include <cstdlib>

class Player;

class Monster :
	public Actor
{
private: bool isCollided = false;
		 bool invincibility = false;
		 int t0;
public:
	Monster();
	Monster(const char* textureSheet, int x, int y);
	Monster(const Monster & a);
	Monster & operator=(const Monster & a);
	void update(int weakness);
	void pathFinding(Player * p);
	~Monster();
	void bombHit();
	void collideWith(Attack * m);



	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

	void isInvulnerable();

};

