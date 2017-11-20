#pragma once
#include "Actor.h"
#include "Collider.h"
#include "Player.h"
#include "Attack.h"
#include <cstdlib>
class Boss :
	public Actor
{
private: bool isCollided = false;
		 bool invincibility = false;
		 int t0;
public:
	Boss();
	Boss(const char* textureSheet, int x, int y);
	void update(int weakness);
	//void update() override;
	void pathFinding(Player * p);
	~Boss();
	void collideWith(Attack * m);

	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

	void isInvulnerable();

};

