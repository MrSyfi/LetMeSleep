#pragma once
#include "GameObject.h"
class Actor :
	public GameObject
{
private:
	int health;

public:
	Actor();
	Actor(const char* textureSheet, int x, int y);
	// The Player and Monsters don't have the same behaviour..
	// Actor's update needs to be virtual.
	virtual void update(int i) = 0;
	void move(int i);
	void stopMove();
	~Actor();
	int getHealth() { return health; }
	void setHealth(int health) { this->health = health;}

protected:
	int dx, dy;
};

