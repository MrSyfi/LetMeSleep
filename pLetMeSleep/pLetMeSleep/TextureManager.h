#pragma once

#include "Game.h"

class TextureManager
{
public:

	//This function can load a texture in a renderer. (Image + renderer)
	static SDL_Texture* LoadTexture(const char* fileName);
	//string LoadText(string text);
	static void draw(SDL_Texture* text, SDL_Rect srcRect, SDL_Rect destRect);
	//static void draw(string text, SDL_Rect srcRect, SDL_Rect destRect);
	TextureManager();
	~TextureManager();

private :	
	//Sets the black color for the text
	SDL_Color black = { 0,0,0 };
};

