#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "Button.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "ECSystem.h"
#include "Components.h"
#include "time.h"
#include "Attack.h"
#include <vector>

std::vector<Attack> attacks;

std::vector<Monster> enemys;
std::vector<Button> buttons;
Player* player;
Monster* enemy, *enemy2;
Map* map;
Button* start;
Button* quit;
SDL_Renderer* Game::renderer = nullptr;
//Allows to not spam the attacks
struct tm instant;
Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{
}


Game::~Game()
{
}

int  Game::getScreenHeight() {
	return SCREEN_HEIGHT;
}

int  Game::getScreenWidth() {
	return SCREEN_WIDTH;
}

void Game::buildGame(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen) {

		flags = SDL_WINDOW_FULLSCREEN;	//Define if the game is in fullscreen or not

	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {	//If the subsystem is not initialised..


		std::cout << "Subsystem Initialised!..." << std::endl;

		//Create a window(Title, dimensions, size and flag)
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {	//If the window is created..

			std::cout << "Window created ! " << std::endl;

		}


		//Create a rendering context for the window
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) { //If the renderer is created..

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created ! " << std::endl;

		}

		isRunning = true;
		//player = new Player("drawable/player.gif", 10, 40);
		//enemy = new Monster(("drawable/prof"+std::to_string(randomNbMonster(3))+".gif").c_str(), 100, 400);
		start = new Button("drawable/start.gif", 192, 256);
		quit = new Button("drawable/start.gif", 192, 384);
		buttons.push_back(*start);
		buttons.push_back(*quit);
		map = new Map();

		newPlayer.addComponent<PositionComponent>();


	}
	else {

		isRunning = false;

	}



}

void Game::attack(int i) {
	//Uses the Attack class to create an attack that will go in a direction, following the i code

	//The user will need to wait that a bit between each attack$
	long delta = SDL_GetTicks() - t0;
	if (delta > 500) {
		int x = player->getX() + 16;
		int y = player->getY() + 16;
		Attack * at = new Attack("drawable/animShoot.gif", x, y);
		at->move(i);
		attacks.push_back(*at);
		t0 = SDL_GetTicks();
	}
}



void Game::clickStart() {
	player = new Player("drawable/player.gif", 10, 40);
	enemy = new Monster(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), 100, 400);
	enemy2 = new Monster(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), 400, 400);
	enemys.push_back(*enemy);
	enemys.push_back(*enemy2);
	map->addMap();
	std::cout << "SECOND" << std::endl;
}

int Game::randomNbMonster(int max) {
	srand(time(NULL));
	return std::rand() % max + 1;
}


void Game::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {

		//If the user close the windows..
	case SDL_QUIT:
		isRunning = false;	//The game loop is interrupted.
		break;

		//Allows the player to move in a direction following the pressed key
	case SDL_KEYDOWN:
		if (player != nullptr) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_UP: player->move(0);      break;
			case SDL_SCANCODE_DOWN:	player->move(1); break;
			case SDL_SCANCODE_LEFT:	player->move(2);  break;
			case SDL_SCANCODE_RIGHT:player->move(3); 	break;
			case SDL_SCANCODE_ESCAPE: isRunning = false; break;
			case SDL_SCANCODE_W: attack(0); break;
			case SDL_SCANCODE_S: attack(1); break;
			case SDL_SCANCODE_A: attack(2); break;
			case SDL_SCANCODE_D: attack(3); break;
			default: break;
			}
		}
		break;

		//Stops the actual movement once the key has been released
	case SDL_KEYUP:
		if (player != nullptr) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_UP: player->stopMove();      break;
			case SDL_SCANCODE_DOWN:	player->stopMove(); break;
			case SDL_SCANCODE_LEFT:	player->stopMove();  break;
			case SDL_SCANCODE_RIGHT:player->stopMove(); 	break;
			default: break;
			}
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (buttons.size() != 0) {
			//Checks if the right or left click is on top of the menu buttons
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (buttons.at(0).isOnTop(x, y)) {
				for (int i = 0; i < buttons.size(); i++) {
					buttons.erase(buttons.begin() + i);
				}
				std::cout << "FIRST" << std::endl;
				buttons.clear();
				clickStart();
			}
			else if (buttons.at(1).isOnTop(x, y)) {
				isRunning = false;
			}
		}

	default:
		break;

	}
}

void Game::updateGame() {

	if (player != nullptr) {
		if (player->getHealth() == 0) {
			delete player;
			player = nullptr;
			if (enemys.size() != 0) {
				for (int i = 0; i < enemys.size(); i++) {
					enemys.erase(enemys.begin() + i);
				}
				enemys.clear();
			}
			if (attacks.size() != 0) {
				for (int i = 0; i < attacks.size(); i++) {
					attacks.erase(attacks.begin() + i);
				}
				attacks.clear();
			}
		}
		else {
			player->update();
			if (enemys.size() != 0) {
				for (int i = 0; i < enemys.size(); i++) {
					Monster * m = new Monster(enemys.at(i));
					player->collideWith(m);
				}
			}
		}

	}

	if (enemys.size() != 0) {

		for (int i = 0; i < enemys.size(); ) {
			if (enemys.at(i).getHealth() == 0) {
				enemys.erase(enemys.begin() + i);
			}
			else {
				enemys.at(i).update();
				if (player != nullptr) {
					enemys.at(i).pathFinding(player);
				}
				if (attacks.size() != 0) {
					for (int j = 0; j < attacks.size(); j++) {
						enemys.at(i).collideWith(new Attack(attacks.at(j)));
					}
				}
				i++;
			}
		}
	}


	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size();) {
			if (attacks.at(i).getX() >= 640 || attacks.at(i).getX() <= 0 || attacks.at(i).getY() <= 0 || attacks.at(i).getY() >= 640) {
				attacks.erase(attacks.begin() + i);
				std::cout << "PROJECTILE EFFACE" << std::endl;
			}
			else {
				attacks.at(i).update();
				i++;
			}
		}

	}

	if (buttons.size() != 0) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons.at(i).update();
		}
	}

	manager.update();


	/*std::cout << newPlayer.getComponent<PositionComponent>().getX() << "," <<
		newPlayer.getComponent<PositionComponent>().getY() << std::endl;*/

}

void Game::drawGame() {

	//Clear the rendering target
	SDL_RenderClear(renderer);

	//This is where we would add stuff to render;
	map->drawMap();
	if (player != nullptr) 	player->drawGameObject();
	if (enemys.size() != 0) {
		for (int i = 0; i < enemys.size(); i++) {
			enemys.at(i).drawGameObject();
		}
	}
	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			attacks.at(i).drawGameObject();
		}
	}

	if (buttons.size() != 0) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons.at(i).drawGameObject();
		}
	}
	//Update the screen
	SDL_RenderPresent(renderer);

}

void Game::destroyGame() {


	//Destroy the window
	SDL_DestroyWindow(window);

	//Destroy the renderer
	SDL_DestroyRenderer(renderer);
	if (player != nullptr) 	delete player;

	if (enemys.size() != 0) {
		for (int i = 0; i < enemys.size(); i++) {
			enemys.erase(enemys.begin() + i);
		}
		enemys.clear();
	}

	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) {
			attacks.erase(attacks.begin() + i);
		}

		attacks.clear();
	}
	//Destroy the subsystem
	SDL_Quit();
	std::cout << "The game is cleared" << std::endl;

}


