#pragma once
class Player;

/*
* Abstract class who
* manage the possible collision with the Hero.
*/
class Collider
{
public:
	Collider();
	virtual void collideWithHero(Player p) = 0;
	~Collider();
};

