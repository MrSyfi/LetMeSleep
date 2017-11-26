#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Game
{
public:
	Game();
	~Game();

	int getScreenHeight();

	int getScreenWidth();

	void buildGame(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);	//This function build the game.


	void attack(int i);

	void clickStart();

	void addEnemies();

	void addBoss();		//Adds the boss tho the map

	int randomPosition(int i);

	int randomNbMonster(int max);
																									//This function allows to apply an image to a surface.
	void handleEvents();																			//This function handle the events like closing the windows.
	void updateGame();

	void drawGame();																				//This function manage the renderer.
	void destroyGame();																				//This function destroy the game.
	void destroyAllEntities();																		//This function removes all entities present from the game.
	bool running() { return isRunning; }

	static SDL_Renderer *renderer;


private:
	//Screen size parameters
	const int SCREEN_WIDTH = 1080;
	const int SCREEN_HEIGHT = 1080;
	const int SCREEN_BPP = 32;
	//Les surfaces que nous allons utiliser 
	SDL_Surface *message = NULL;
	SDL_Surface *background = NULL;
	SDL_Surface *screen = NULL;
	int cnt = 0;
	bool isRunning;																					//This variable can stop the game loop when the user leave the game.
	SDL_Window *window;

	//Defense of the player and weakness of the enemies
	int defense = 5;
	int weakness = 2;
	//Allows to set the time between attacks
	int t0;

	//Changes the type of button we are using
	int buttonType;

	//Will define if the game is in Pause or not
	bool pause = false;
};


