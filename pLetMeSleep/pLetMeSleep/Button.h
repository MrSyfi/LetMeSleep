#pragma once
#include "Actor.h"
class Button :
	public Actor
{
public:
	Button(const char* textureSheet, int x, int y);
	Button();
	~Button();
	Button(const Button & a);
	bool isOnTop(int mouseX, int mouseY);
	
	Button& operator=(const Button& a);

	void update(int i) override;
};

