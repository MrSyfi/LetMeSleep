#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class Collider;

class Game
{
public:
	Game();
	~Game();

	int getScreenHeight();

	int getScreenWidth();

	void buildGame(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);	//This function build the game.

	void timer();



	void attack(int i);

	void menuButtons();

	void clickStart();

	void addEnemies();

	void addBoss();		//Adds the boss tho the map

	int randomPosition(int i);

	int randomNbMonster(int max);
																									//This function allows to apply an image to a surface.
	void handleEvents();																			//This function handle the events like closing the windows.
	void damageAllEnemies();
	void updateGame();

	void drawGame();																				//This function manage the renderer.
	void destroyGame();																				//This function destroy the game.
	void destroyAllEntities();																		//This function removes all entities present from the game.
	bool running() { return isRunning; }

	static void addTitle(int id, int x, int y);
	void newRoom();
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static std::vector<Collider*> colliders;


private:
	//Screen size parameters
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	//Les surfaces que nous allons utiliser 
	SDL_Surface *message = NULL;
	SDL_Surface *background = NULL;
	SDL_Surface *screen = NULL;
	int cnt = 0;
	bool isRunning;																					//This variable can stop the game loop when the user leave the game.
	SDL_Window *window;

	//Defines if the application is in fullscreen
	bool fullscreen = false;

	//Defense of the player and weakness of the enemies
	int defense = 5;
	int weakness = 2;
	//Allows to set the time between attacks
	int t0, tButton;

	//Defines if the buttons can be used or not, with a timer
	bool buttonFrame=true;

	//The size of the screen
	int widthscreen, heightscreen;

	//Changes the type of button we are using
	int buttonType;

	//Will define if the game is in Pause or not
	bool pause = false;

	//Corresponds to the score the player will make	 during a game
	int score;


};


