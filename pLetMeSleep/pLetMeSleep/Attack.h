#pragma once
#include "GameObject.h"
#include <iostream>
class Attack :
	public GameObject
{
private:
	
public:
	void move(int i);
	void update(int i);
	void stopMove();
	Attack();
	~Attack();
	Attack(const char* textureSheet, int x, int y);

	Attack(const Attack &a);
	Attack & operator=(const Attack & a);
protected:
	int dx, dy;
};
