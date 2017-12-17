#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject()
{
}

GameObject::GameObject(const char* textureSheet, int x, int y)
{

	entTexture = TextureManager::LoadTexture(textureSheet);
	xpos = x;
	ypos = y;
	
}

GameObject::~GameObject()
{
}

void GameObject::update(int i) {
	
	drawGameObject();
}

void GameObject::drawGameObject() {

	//Copy the texture to the renderer. (Renderer, texture, src rectangle, dst rectangle (Both NULL if we want the texture in all the renderer)
	SDL_RenderCopy(Game::renderer, entTexture, &srcRect, &destRect);

}

//Manages a collision between the GameObject and another one
bool GameObject::collision(SDL_Rect  tmpRect) {
	if ((tmpRect.x >= this->destRect.x + this->destRect.w) || (tmpRect.x + tmpRect.w <= this->destRect.x) || (tmpRect.y >= this->destRect.y + this->destRect.h) || (tmpRect.y + this->destRect.h <= this->destRect.y)) return false;
	return true;
}

GameObject::GameObject(const GameObject & g)
{
	this->entTexture = g.entTexture;
	this->xpos = g.xpos;
	this->ypos = g.ypos;
}

GameObject & GameObject::operator=(const GameObject & g)
{
	if (&g != this) {
		this->entTexture = g.entTexture;
		this->xpos = g.xpos;
		this->ypos = g.ypos;
	}
	return *this;
}
