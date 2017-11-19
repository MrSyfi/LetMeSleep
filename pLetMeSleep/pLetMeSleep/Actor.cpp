#include "Actor.h"

Actor::Actor()
{
}

Actor::Actor(const char * textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
}
// Only actors can move.
// Following the direction we want, we set velocity variable (dx, dy) to -1, 0 or 1.
void Actor::move(int i)
{
	// Actor's (Monsters,Player) movement.
	switch (i) {
		// Up
	case 0: dx = 0; dy = -1; break;
		// Down
	case 1: dx = 0; dy = 1; break;
		// Right
	case 2: dx = -1; dy = 0; break;
		// Left
	case 3: dx = 1; dy = 0; break;
	default: dx = dy = 0; break;
	}
}

// When we stop moving, both velocity variables are equal to 0
void Actor::stopMove()
{
	dx = dy = 0;
}

Actor::~Actor()
{
}


