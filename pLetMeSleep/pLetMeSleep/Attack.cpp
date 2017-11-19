#include "Attack.h"
Attack::Attack()
{
}

Attack::~Attack()
{
}

Attack::Attack(const char * textureSheet, int x, int y) : GameObject(textureSheet, x, y)
{
}


void Attack::move(int i)
{
	switch (i) {
		case 0: dx = 0; dy = -1; std::cout << dx << " , " << dy << std::endl;  break; // AttackUp
		case 1: dx = 0; dy = 1; std::cout << dx << " , " << dy << std::endl; break; // AttackDown
		case 2: dx = -1; dy = 0; std::cout << dx << " , " << dy << std::endl; break; // AttackLeft
		case 3: dx = 1; dy = 0; std::cout << dx << " , " << dy << std::endl; break; //AttackRight
		default: break;
	}
}

void Attack::update()
{

		xpos += dx*3;
		ypos += dy*3;

	srcRect.h = 16;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;


	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

}

void Attack::stopMove() {
	//Will stop moving if hits an enemy or a wall
}

