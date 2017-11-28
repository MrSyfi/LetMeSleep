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
#include "Item.h"
#include "Boss.h"
#include "Container.h"
#include <vector>

using std::vector;

vector<Attack> attacks;
vector<Monster> enemys;
vector<Button> buttons;
vector<Container> containers;
Player* player;
Container* menu_logo, *pause_logo, *about_logo;
Monster* enemy, *enemy2, *enemy3;
Map* map;
Boss* boss;
Button* start, *quit, *gameEnded, *pauseButton, *mainMenu, *about;
Item* item;
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

		//Launches the TTF library from SDL to show text on the screen
		
		


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
		


		menuButtons();
		buttonType = 0;
		map = new Map();
		boss = nullptr;
		//Will seed the random at the beginning of the application for further needs
		srand(time(NULL));
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

void Game::menuButtons() {
	//This method will add the buttons inside the menu to the screen.
	start = new Button("drawable/button_start.gif", 192, 256);
	about = new Button("drawable/button_about.gif", 192, 384);
	quit = new Button("drawable/button_exit.gif", 192, 512);

	buttons.push_back(*start);
	buttons.push_back(*about);
	buttons.push_back(*quit);


	menu_logo = new Container("drawable/menu_logo.gif",85, 20, 225, 100);
	containers.push_back(*menu_logo);
}

void Game::clickStart() {
	//This method will create the player, change the map and add new enemies to the room.
	player = new Player("drawable/player.gif", 10, 40);
	addEnemies();
	map->addMap();
}

void Game::addEnemies() {
	//Adds the enemies to the current map
	enemy = new Monster(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), randomPosition(player->getX()), randomPosition(player->getY()));
	enemy2 = new Monster(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), randomPosition(player->getX()), randomPosition(player->getY()));
	enemy3 = new Monster(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), randomPosition(player->getX()), randomPosition(player->getY()));
	enemys.push_back(*enemy);
	enemys.push_back(*enemy2);
	enemys.push_back(*enemy3);
}

void Game::addBoss() {
	boss = new Boss("drawable/boss.gif", 320, 320);
}
int Game::randomPosition(int i) {
	//Gives a random X or Y to the enemy, while being at at least 50 pixels from the player

	return std::rand() % 640;
}

int Game::randomNbMonster(int max) {
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
			case SDL_SCANCODE_W: player->move(0);      break;
			case SDL_SCANCODE_S:	player->move(1); break;
			case SDL_SCANCODE_A:	player->move(2);  break;
			case SDL_SCANCODE_D:player->move(3); 	break;
			case SDL_SCANCODE_ESCAPE:
				//If we are not on the mainMenu, the escape key will do something
				if (buttonType != 0) {
					//If we are in pause, we quit the pause, if we are not, we get in pause
					if (!pause) {
						pause = true;
						buttonType = 1;
						pauseButton = new Button("drawable/button_resume.gif", 192, 256);
						mainMenu = new Button("drawable/button_main_menu.gif", 192, 384);
						buttons.push_back(*pauseButton);
						buttons.push_back(*mainMenu);
						pause_logo = new Container("drawable/endButton.jpg", 82, 20, 225, 100);
						containers.push_back(*pause_logo);
					}
					else {
						pause = false;
						buttonType = 2;
						buttons.erase(buttons.begin());
						buttons.clear();
						containers.erase(containers.begin());
					}
				}; break;
			case SDL_SCANCODE_UP: attack(0); break;
			case SDL_SCANCODE_DOWN: attack(1); break;
			case SDL_SCANCODE_LEFT: attack(2); break;
			case SDL_SCANCODE_RIGHT: attack(3); break;
			default: break;
			}
		}
		break;

		//Stops the actual movement once the key has been released
	case SDL_KEYUP:
		if (player != nullptr) {
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_W: player->stopMove();      break;
			case SDL_SCANCODE_S:	player->stopMove(); break;
			case SDL_SCANCODE_A:	player->stopMove();  break;
			case SDL_SCANCODE_D:player->stopMove(); 	break;
			default: break;
			}
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		//Checks if the left or right click button is pressed when the mouse is placed on the button
		if (buttons.size() != 0) {
			//Checks if the right or left click is on top of the menu buttons
			int x, y;
			SDL_GetMouseState(&x, &y);
			switch (buttonType) {
			case 0: //MainMenu
				if (buttons.at(0).isOnTop(x, y)) {
					for (int i = 0; i < buttons.size(); i++) {
						buttons.erase(buttons.begin() + i);
					}
					buttons.clear();
					clickStart();
					containers.erase(containers.begin());
					buttonType = 2;
				}
				else if (buttons.at(1).isOnTop(x, y)) {
					buttonType = 3;
					for (int i = 0; i < buttons.size(); i++) {
						buttons.erase(buttons.begin() + i);
					}
					buttons.clear();
					containers.erase(containers.begin());
					about_logo = new Container("drawable/about_container.gif", 0, 0, 320, 188);
					containers.push_back(*about_logo);
					mainMenu = new Button("drawable/button_main_menu.gif", 192, 384);
					buttons.push_back(*mainMenu);

				}
				else if (buttons.at(2).isOnTop(x, y)) {
					isRunning = false;
				}
				; break;
			case  1: //Game has been paused
				if (buttons.at(0).isOnTop(x, y)) {

					pause = false;
					buttonType = 2;
					buttons.erase(buttons.begin());
					buttons.clear();
				}
				else if(buttons.at(1).isOnTop(x,y)){
					pause = false;
					//Go back to main menu so we destroy all the entities
					destroyAllEntities();
					buttons.erase(buttons.begin());
					buttons.erase(buttons.begin());
					buttons.clear();
					buttonType = 0;
					menuButtons();
					//Reset of all the upgrades
					weakness = 2;
					defense = 5;
					
				}
				;
				break;
			case 2: //Game over (player dead, boss beaten)
				if (buttons.at(0).isOnTop(x, y)) {
					buttons.erase(buttons.begin());
					buttons.clear();
					menuButtons();
					buttonType = 0;
				}; break;
			case 3 : 
				if (buttons.at(0).isOnTop(x, y)) {
					//Once the About button has been pressed again, we go back to the main menu
					buttons.erase(buttons.begin());
					buttons.clear();
					containers.erase(containers.begin());
					menuButtons();
					buttonType = 0;
				}
				
			default: break;
			}
		}

	default:
		break;

	}
}

void Game::updateGame() {
	if (!pause) {
		if (player != nullptr) {
			if (player->getHealth() <= 0) {
				//Destroy all the current entities, remove the current layout and adds the gameover Button
				destroyAllEntities();
				map->loadMap("map_layout/layout_menu.txt");
				containers.push_back(*menu_logo);
				gameEnded = new Button("drawable/button_game_over.gif", 192, 256);
				buttons.push_back(*gameEnded);

			}
			else {
				player->update(defense);
				if (boss != nullptr) {
					player->collideWith(boss);
				}
				if (enemys.size() != 0) {
					for (int i = 0; i < enemys.size(); i++) {
						//Will check only if the player has not collided the previous enemies
						if (!player->isColl()) {
							player->collideWith(new Monster(enemys[i]));
						}
					}
				}
				else {
					if (boss == nullptr) {
						//Changes the room when all enemies have been killed and the player steps on one of the arrows
						//As it is a sort of random maze, the previous room is not saved in memory
						if (player->getX() >= 600 && player->getY() >= 270 && player->getY() <= 320) {
							//ArrowRight
							int rand = randomNbMonster(10);
							if (rand == 1) {
								addBoss();
								map->loadMap("map_layout/layout_boss.txt");
								if (enemys.size() != 0) {
									for (int i = 0; i < enemys.size(); i++) {
										enemys.erase(enemys.begin() + i);
									}
									enemys.clear();
								}
							}
							else {
								addEnemies();
								map->addMap();
							}
							player->setX(0);
							player->newRoom();
							if (item != nullptr) {
								delete item;
								item = nullptr;
							}
						}
						else if (player->getY() >= 600 && player->getX() >= 270 && player->getX() <= 320) {
							int rand = randomNbMonster(10);
							if (rand == 1) {
								addBoss();
								map->loadMap("map_layout/layout_boss.txt");
								if (enemys.size() != 0) {
									for (int i = 0; i < enemys.size(); i++) {
										enemys.erase(enemys.begin() + i);
									}
									enemys.clear();
								}
							}
							else {
								addEnemies();
								map->addMap();
							}
							player->setY(0);
							player->newRoom();
							if (item != nullptr) {
								delete item;
								item = nullptr;
							}
						}
						else if (player->getX() <= 40 && player->getY() >= 270 && player->getY() <= 320) {
							//ArrowLeft
							int rand = randomNbMonster(10);
							if (rand == 1) {
								addBoss();
								map->loadMap("map_layout/layout_boss.txt");
								if (enemys.size() != 0) {
									for (int i = 0; i < enemys.size(); i++) {
										enemys.erase(enemys.begin() + i);
									}
									enemys.clear();
								}
							}
							else {
								addEnemies();
								map->addMap();
							}
							player->setX(600);
							player->newRoom();
							if (item != nullptr) {
								delete item;
								item = nullptr;
							}
						}
						else if (player->getY() <= 40 && player->getX() >= 270 && player->getX() <= 320) {
							//ArrowTop
							int rand = randomNbMonster(10);
							if (rand == 1) {
								addBoss();
								map->loadMap("map_layout/layout_boss.txt");
								if (enemys.size() != 0) {
									for (int i = 0; i < enemys.size(); i++) {
										enemys.erase(enemys.begin() + i);
									}
									enemys.clear();
								}
							}
							else {
								addEnemies();
								map->addMap();
							}
							player->setY(600);
							player->newRoom();
							if (item != nullptr) {
								delete item;
								item = nullptr;
							}
						}
					}
				}
			}

		}

		if (enemys.size() != 0) {

			for (int i = 0; i < enemys.size(); ) {
				if (enemys.at(i).getHealth() <= 0) {
					if (item == nullptr) {
						int rand = std::rand() % 10 + 1;
						if (rand == 1) {
							item = new Item("drawable/book_normal.gif", enemys.at(i).getX(), enemys.at(i).getY());
						}
					}
					enemys.erase(enemys.begin() + i);

				}
				else {
					enemys.at(i).update(weakness);
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
				}
				else {
					attacks.at(i).update(0);
					i++;
				}
			}
		}

		if (item != nullptr) {
			item->update(0);
			item->collideWith(player);
			if (item->isColl()) {
				if (item->isDefense()) {
					if (defense > 3) {
						defense--;
					}
				}
				else {
					if (weakness <= 2) {
						weakness++;
					}
				}
				delete item;
				item = nullptr;
			}
		}

		if (boss != nullptr) {

			if (boss->getHealth() <= 0) {
				//When the boss is dead, we go to the Game over menu
				destroyAllEntities();
				containers.push_back(*menu_logo);
				map->loadMap("map_layout/layout_menu.txt");
				gameEnded = new Button("drawable/button_game_over.gif", 192, 256);
				buttons.push_back(*gameEnded);

			}
			else {
				boss->update(weakness);
				if (player != nullptr) {
					boss->pathFinding(player);
				}
				if (attacks.size() != 0) {
					for (int j = 0; j < attacks.size(); j++) {
						boss->collideWith(new Attack(attacks.at(j)));
					}
				}
			}
		}
	}
	if (buttons.size() != 0) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons.at(i).update(0);
		}
	}

	if (containers.size() != 0) {
		for (int i = 0; i < containers.size(); i++) {
			containers.at(i).update(0);
		}
	}
	manager.update();
}

void Game::drawGame() {

	//Clear the rendering target
	SDL_RenderClear(renderer);

	//This is where we would add stuff to render;
	map->drawMap();
	if (!pause) {
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
		if (boss != nullptr) {
			boss->drawGameObject();
		}
		if (item != nullptr) {
			item->drawGameObject();
		}
	}
	if (buttons.size() != 0) {
		for (int i = 0; i < buttons.size(); i++) {
			buttons.at(i).drawGameObject();
		}
	}

	if (containers.size() != 0) {
		for (int i = 0; i < containers.size(); i++) {
			containers.at(i).drawGameObject();
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

	
	destroyAllEntities();
	//Destroy the subsystem
	
	SDL_Quit();
	std::cout << "The game is cleared" << std::endl;

}


void Game::destroyAllEntities() {

	if (player != nullptr) {
		delete player;
		player = nullptr;
	}

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
	if (boss != nullptr) {
		delete boss;
		boss = nullptr;
	}
	
	if (item != nullptr) {
		delete item;
		item = nullptr;
	}
	if (containers.size() != 0) {
		for (int i = 0; i < containers.size(); i++) {
			containers.erase(containers.begin() + i);
		}
		containers.clear();
	}
}


