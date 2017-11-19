#pragma once
#include "ECSystem.h"


class PositionComponent : public Component {

private:

	int xpos;
	int ypos;

public:

	int getX(){ return xpos; }
	int getY() { return ypos; }

	void init() override {

		xpos = 0;
		ypos = 0;

	}

	void update() override {

		xpos++;
		ypos++;

	}

	void setPos(int x, int y) {

		xpos = x;
		ypos = y;

	}

};

