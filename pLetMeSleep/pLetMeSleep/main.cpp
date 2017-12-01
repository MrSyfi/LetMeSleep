#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"


Game *game = nullptr;

int main(int argc, char *argv[]) {

	//Frames per seconds
	const int FPS = 120;
	//The length time that each of the frames will be displayed
	const int frameDelay = 1000 / FPS;

	//The type is a massive Integer because the frameStart can be long as 49 days of running
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->buildGame("Let me sleep", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, true);

	while (game->running()) {

		//We get the numbers of milliseconds since the SDL library is initialized.
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->updateGame();
		game->drawGame();

		//We get the time during the game perform all this methods.
		frameTime = SDL_GetTicks() - frameStart;


		if (frameDelay > frameTime) {

			//The frame wait during the delay
			SDL_Delay(frameDelay - frameTime);

		} 


	}

	game->destroyGame();

	system("pause");

	return 0;

}