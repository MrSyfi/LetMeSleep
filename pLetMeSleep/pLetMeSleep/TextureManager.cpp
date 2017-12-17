#include "TextureManager.h"

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

SDL_Texture* TextureManager::LoadTexture(const char* filename) {

	//Representation of the surface which displays the image
	SDL_Surface* tempSurface = IMG_Load(filename);
	//We inject the surface in our texture
	SDL_Texture* text = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	//We clean the temporary surface
	SDL_FreeSurface(tempSurface);
	return text;

}


void TextureManager::draw(SDL_Texture* text, SDL_Rect srcRect, SDL_Rect destRect) {

	SDL_RenderCopy(Game::renderer, text, &srcRect, &destRect);

}