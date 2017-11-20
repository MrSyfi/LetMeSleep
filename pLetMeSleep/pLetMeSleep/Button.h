#pragma once
#include "Actor.h"
class Button :
	public Actor
{
public:
	Button(const char* textureSheet, int x, int y);
	Button();
	~Button();
	bool isOnTop(int mouseX, int mouseY);

	void update(int i) override;
};

