#pragma once
#include "GameObject.h"
class Container :
	public GameObject
{
private:
	int modx, mody;
	//Will allow to have different heights and width for the containers

public:
	Container();
	Container(const char * textureSheet, int x, int y, int modx, int mody);
	void update(int i);

	Container& operator=(const Container& a);
	Container(const Container & a);

	~Container();
};

