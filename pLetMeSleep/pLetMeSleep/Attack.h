#pragma once
#include "GameObject.h"
#include <iostream>
class Attack :
	public GameObject
{
private:
	
public:
	void move(int i);
	void update();
	void stopMove();
	Attack();
	~Attack();
	Attack(const char* textureSheet, int x, int y);
protected:
	int dx, dy;
};
