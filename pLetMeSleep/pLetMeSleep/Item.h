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
	//Item(const char * textureSheet, int x, int y, bool isActive);
	//Item(const char * textureSheet, int x, int y);
	~Item();
	void update(int i);
	void createItem(); //Will create either an upgrade for the player damage or player defense
	bool isColl();
	//bool isActi();
	bool isDefense();
	void collideWith(Player * p);
	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	int getType() { return type; }
private: bool defense;
		 bool isCollided = false;
		 int type;
};

