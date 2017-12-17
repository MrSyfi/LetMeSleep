#pragma once
#include "GameObject.h"
#include "time.h"
#include "Player.h"
class Item :
	public GameObject
{
public:
	Item();
	Item(const char * textureSheet, int x, int y, int type);
	~Item();
	Item(const Item & a);
	Item& operator=(const Item& a);
	void update(int i);
	void createItem(); //Will create either an upgrade for the player damage or player defense
	bool isColl();
	bool isDefense();

	void collideWith(Player * p); //Simple collision algorithm
	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	int getType() { return type; } //Returns the type of the object
private: bool defense;
		 bool isCollided = false;
		 int type;
};

