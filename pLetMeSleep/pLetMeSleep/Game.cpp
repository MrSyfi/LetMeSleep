#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "Button.h"
#include "GameObject.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "time.h"
#include "Attack.h"
#include "Item.h"
#include "Boss.h"
#include "SDL_ttf.h"
#include "Container.h"
#include <vector>
using std::vector;

vector<Attack> attacks;
vector<Monster> enemys;
vector<Button> buttons;
vector<Container> containers;
vector<Item> items;
Player* player;
Container *menu_logo, *pause_logo, *about_logo, *tuto;
Monster* enemy;
Map* map;
Boss* boss;
Button* start, *quit, *gameEnded, *pauseButton, *mainMenu, *about;
Item* item;
SDL_Renderer* Game::renderer = nullptr;

SDL_Event Game::event;

const int Game::DEAD_ZONE = 15000;


Game::Game()
{
}


Game::~Game()
{
}

int  Game::getScreenHeight() {
	return heightscreen;
}

int  Game::getScreenWidth() {
	return widthscreen;
}

void Game::buildGame(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flags = 0;
	if (fullscreen) {
		this->fullscreen = true;
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;	//Define if the game is in fullscreen or not
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) == 0) {	//If the subsystem is not initialised..
		std::cout << "Subsystem Initialised!..." << std::endl;
		//Create a window(Title, dimensions, size and flag)
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {	//If the window is created..
			std::cout << "Window created ! " << std::endl;
		}
		//Will set the window size for width and height values
		SDL_GetWindowSize(window, &widthscreen, &heightscreen);
		//Create a rendering context for the window
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) { //If the renderer is created..
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created ! " << std::endl;
		}
		isRunning = true;
		map = new Map(getScreenWidth(), getScreenHeight());
		//Display the start menu
		menuButtons();
		//Change the type of the menu's button
		buttonType = 0;
		boss = nullptr;
		//Will seed the random at the beginning of the application for further needs
		srand(time(NULL));
	}
	else {
		isRunning = false;
	}
}

void Game::timer() {
	//Defines if the user can press a button or not at the moment
	long delta = SDL_GetTicks() - tButton;
	//Buttons can be used again after 0.2s
	if (delta > 200) {
		buttonFrame = true;
		tButton = SDL_GetTicks();
	}
}

void Game::attack(int i) {
	//Uses the Attack class to create an attack that will go in a direction, following the i code
	//The user will need to wait that a bit between each attack$
	long delta = SDL_GetTicks() - t0;
	if (delta > 500) {
		int x = player->getX() + 16; //16 is the middle part of the player
		int y = player->getY() + 16;
		Attack * at = new Attack("drawable/animShoot.gif", x, y);
		at->move(i);
		attacks.push_back(*at);
		//We start again the timer
		t0 = SDL_GetTicks();
	}
}

void Game::menuButtons() {
	//This method will add the buttons inside the menu to the screen.
	start = new Button("drawable/button_start.gif", getScreenWidth() / 2 - 160, 256);
	about = new Button("drawable/button_about.gif", getScreenWidth() / 2 - 160, 384);
	quit = new Button("drawable/button_exit.gif", getScreenWidth() / 2 - 160, 512);
	//We add the buttons to the buttons vector
	buttons.push_back(*start);
	buttons.push_back(*about);
	buttons.push_back(*quit);
	//We load the layout we use for the menu, with the LetMeSleep logo over it
	map->loadMap("map_layouts/layout_menu.txt");
	menu_logo = new Container("drawable/menu_logo.gif", getScreenWidth() / 2 - 225, 50, 225, 100);
	containers.push_back(*menu_logo);
}

void Game::clickStart() {
	//This method will create the player, change the map and add new enemies to the room.
	player = new Player("drawable/player.gif", 10, 40);
	addEnemies();
	//We load a random map
	map->addMap();
}

void Game::addEnemies() {
	//Adds the enemies to the current map
	for (int i = 0; i < 5; i++) {
		enemy = new Monster(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), randomPosition(1), randomPosition(2));
		enemys.push_back(*enemy);
	}
}

void Game::addBoss() {
	//Add the boss on the map
	boss = new Boss(("drawable/prof" + std::to_string(randomNbMonster(3)) + ".gif").c_str(), getScreenWidth()/2, getScreenHeight()/2);
}
int Game::randomPosition(int i) {
	//Gives a random X or Y to the enemy, while being at at least 50 pixels from the player
	if (i == 1) return std::rand() % 1216 + 64;
	return std::rand() % 608 + 32;
}

int Game::randomNbMonster(int max) {
	return std::rand() % max + 1;
}


void Game::handleEvents() {

	while (SDL_PollEvent(&event)) {
		switch (event.type) {

			//If the user close the windows..
		case SDL_QUIT:	isRunning = false;	break; //The game loop is interrupted. 
			//Allows the player to move in a direction following the pressed key
		case SDL_KEYDOWN:
			if (player != nullptr) {
				switch (event.key.keysym.scancode) {
				//The player will move in a different direction following the key the user pressed
				case SDL_SCANCODE_W:	player->move(0); break;
				case SDL_SCANCODE_S:	player->move(1); break;
				case SDL_SCANCODE_A:	player->move(2); break;
				case SDL_SCANCODE_D:	player->move(3); break;
				case SDL_SCANCODE_E: if (player->canActi()) {
					//If the player can use its activable item
					for (int i = 0; i < items.size(); i++) items.erase(items.begin() + i);
					items.clear();
					damageAllEnemies(); //Every enemies gets hit by the "smartphone bomb"
					//The player will need to loot a new activable item to use it again
					player->setActi(false);
				}; break;
				case SDL_SCANCODE_ESCAPE:
					//Triggers the pause
					Pause();
					break;
				//Will trigger an attack at the player's position following the key the user pressed
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
				case SDL_SCANCODE_W: player->stopMove(); break;
				case SDL_SCANCODE_S: player->stopMove(); break;
				case SDL_SCANCODE_A: player->stopMove(); break;
				case SDL_SCANCODE_D: player->stopMove(); break;
				default: break;
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			//Checks if the left or right click button is pressed when the mouse is placed on the button
			if (buttons.size() != 0) {
				timer();
				if (buttonFrame) {
					//Checks if the right or left click is on top of the menu buttons
					int x, y;
					SDL_GetMouseState(&x, &y);
					switch (buttonType) {
					case 0: //MainMenu
						if (buttons.at(0).isOnTop(x, y)) {
							//Triggers the beginning of the game
							for (int i = 0; i < buttons.size(); i++) buttons.erase(buttons.begin() + i);
							buttons.clear();
							containers.erase(containers.begin());
							containers.clear();
							buttonType = 4;
							start = new Button("drawable/button_start.gif", getScreenWidth() / 2 - 160, 500);
							buttons.push_back(*start);
							tuto = new Container("drawable/tutorial.gif", 0, 0, 640, 250);
							containers.push_back(*tuto);
							buttonFrame = false;
						}
						else if (buttons.at(1).isOnTop(x, y)) {
							//Will show informations about the game to the user
							buttonType = 4;
							for (int i = 0; i < buttons.size(); i++) buttons.erase(buttons.begin() + i);
							buttons.clear();
							containers.erase(containers.begin());
							about_logo = new Container("drawable/about_container.gif", getScreenWidth() / 2 - 325, 0, 320, 188);
							containers.push_back(*about_logo);
							mainMenu = new Button("drawable/button_main_menu.gif", getScreenWidth() / 2 - 160, 384);
							buttons.push_back(*mainMenu);
							buttonType = 3;
							buttonFrame = false;
						}
						else if (buttons.at(2).isOnTop(x, y)) {
							//Quits the application by changing isRunning value
							isRunning = false;
						}
						; break;
					case  1: //Game has been paused
						if (buttons.at(0).isOnTop(x, y)) {
							pause = false;
							buttonType = 2;
							containers.erase(containers.begin());
							containers.clear();
							buttons.erase(buttons.begin());
							buttons.clear();
							buttonFrame = false;
						}
						else if (buttons.at(1).isOnTop(x, y)) {
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
							buttonFrame = false;

						}
						;
						break;
					case 2: //Game over (player dead, boss beaten)
						if (buttons.at(0).isOnTop(x, y)) {
							buttons.erase(buttons.begin());
							buttons.clear();
							containers.erase(containers.begin());
							containers.clear();
							menuButtons();
							buttonType = 0;
							buttonFrame = false;
						}; break;
					case 3:
						if (buttons.at(0).isOnTop(x, y)) {
							//Once the A	bout button has been pressed again, we go back to the main menu
							buttons.erase(buttons.begin());
							buttons.clear();
							containers.erase(containers.begin());
							containers.clear();
							menuButtons();
							buttonType = 0;
							buttonFrame = false;
						} break;
					case 4: 
						if (buttons.at(0).isOnTop(x, y)) {
							//After the user has access to the little tutorial, the game can be played
							for (int i = 0; i < buttons.size(); i++) buttons.erase(buttons.begin() + i);
							buttons.clear();
							score = 0;
							clickStart();
							containers.erase(containers.begin());
							buttonType = 2;
							buttonFrame = 0;
						}
					default: break;
					}
				}
			}
		//Gaming controller management
		case SDL_CONTROLLERDEVICEADDED:
			AddController(event.cdevice.which); break;
		case SDL_CONTROLLERDEVICEREMOVED:
			RemoveController(event.cdevice.which); break;
		case SDL_CONTROLLERAXISMOTION:
			OnControllerAxis(event.caxis); break;
		case SDL_CONTROLLERBUTTONDOWN:
			OnControllerButton(event.cbutton); break;
		default:
			break;

		}
	}
}

void Game::damageAllEnemies() {
	if (enemys.size() != 0) {
		for (int i = 0; i < enemys.size(); i++) enemys.at(i).bombHit();
		for (int i = 0; i < items.size(); i++) items.erase(items.begin() + i);
		items.clear();
	}
}

void Game::newRoom() {
	//This method will decide if the next room will be a 
	//boss room or just a normal enemies room
	int rand = randomNbMonster(5);
	//There is a chance out of 5 that the player will enter a boss room
	if (rand == 1) {
		addBoss();
		for (int i = 0; i < enemys.size(); i++) enemys.erase(enemys.begin() + i);
		enemys.clear();
	}
	else {
		addEnemies();
	}
	map->addMap();
	player->newRoom();
	//The items don't change rooms, so we remove them - except the bomb
	for (int i = 0; i < items.size(); i++) {
		if (items.at(i).getType() != 2) items.erase(items.begin() + i);
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
				gameEnded = new Button("drawable/button_game_over.gif", getScreenWidth() / 2 - 160, 256);
				buttons.push_back(*gameEnded);

			}
			else {
				//Defense argument is the defense of the player at a t instant
				player->update(defense);
				if (enemys.size() != 0) {
					for (int i = 0; i < enemys.size(); i++) {
						//Will check only if the player has not collided the previous enemies
						if (!player->isColl()) player->collideWith(new Monster(enemys[i]));
					}
				}
				else {
					//Changes the room when all enemies have been killed and the player steps on one of the doors
					//As it is a sort of random maze where the player is "teleported", the previous room is not saved in memory
					
					//The numbers used are the X and Y values of the doors
					if (player->getX() >= 1216 && player->getY() >= 256 && player->getY() <= 288) {
						//Right
						newRoom();
						player->setX(0);

					}
					else if (player->getY() >= 600 && player->getX() >= 522 && player->getX() <= 588) {
						//Bottom
						newRoom();
						player->setY(0);

					}
					else if (player->getX() <= 40 && player->getY() >= 270 && player->getY() <= 320) {
						//Left
						newRoom();
						player->setX(600);
					}
					else if (player->getY() <= 40 && player->getX() >= 522 && player->getX() <= 588) {

						//Top
						newRoom();
						player->setY(600);
					}
				}
			}
		}
		if (enemys.size() != 0) {
			for (int i = 0; i < enemys.size(); ) {
				if (enemys.at(i).getHealth() <= 0) {
					//When an enemy dies, there is a 20% chance he will drop an item
					int rand = std::rand() % 5 + 1;
					if (rand == 1) {
						//After that, there is 50% chance it is a normal item
						//25% chance it is an activable item
						//25% chance it is a "healing" potion
						int randItem = std::rand() % 3 + 1;
						switch (randItem) {
						case 1: item = new Item("drawable/item.gif", enemys.at(i).getX(), enemys.at(i).getY(), randItem);
							items.push_back(*item); break;
						case 2: item = new Item("drawable/itemActivable.gif", enemys.at(i).getX(), enemys.at(i).getY(), randItem);
							items.push_back(*item);
							break;
						case 3: item = new Item("drawable/healingPotion.gif", enemys.at(i).getX(), enemys.at(i).getY(), randItem);
							items.push_back(*item); break;
						default:break;
						}
					}
					//We finally remove the enemy from the game
					enemys.erase(enemys.begin() + i);

				}
				else {
					//If the enemy is not dead, we update him
					enemys.at(i).update(weakness);
					if (player != nullptr) {
						//Artificial intelligence
						enemys.at(i).pathFinding(player);
					}
					if (attacks.size() != 0) {
						//Collision with the attacks the player has made
						for (int j = 0; j < attacks.size(); j++) {
							enemys.at(i).collideWith(new Attack(attacks.at(j)));
						}
					}
					i++;
				}
			}
		}
		if (boss != nullptr) {
			if (boss->getHealth() <= 0) {
				//When the boss is dead, we go to the Game over menu
				destroyAllEntities();
				containers.push_back(*menu_logo);
				map->loadMap("map_layout/layout_menu.txt");
				gameEnded = new Button("drawable/button_game_over.gif", getScreenWidth() / 2 - 160, 256);
				buttons.push_back(*gameEnded);
			}
			else {
				boss->update(weakness);
				if (player != nullptr) boss->pathFinding(player);
				if (attacks.size() != 0) {
					for (int j = 0; j < attacks.size(); j++) boss->collideWith(new Attack(attacks.at(j)));
				}
			}
		}
		if (attacks.size() != 0) {
			for (int i = 0; i < attacks.size();) {
				if (attacks.at(i).getX() >= 1280 || attacks.at(i).getX() <= 0 || attacks.at(i).getY() <= 0 || attacks.at(i).getY() >= 640) {
					//We erase the attack from the game if it goes out of the screen borders
					attacks.erase(attacks.begin() + i);
				}
				else {
					attacks.at(i).update(0);
					i++;
				}
			}
		}
		if (items.size() != 0) {
			for (int i = 0; i < items.size(); i++) {
				items.at(i).update(0);
				//We check if the player is on the current item
				items.at(i).collideWith(player);
				if (items.at(i).isColl()) {
					//If he is on the current item, we check what type the item is
					switch (items.at(i).getType()) {
					case 1: if (items.at(i).isDefense()) if (defense > 3) defense--; //We update the values of defense or weakness depending of the item
							else if (weakness <= 2) weakness++;
							items.erase(items.begin() + i); break;
					case 2: items.erase(items.begin() + i); //If it is an activable item ,the player can use its smartBomb
						item = new Item("drawable/itemActivable.gif", 0, 0, true);
						items.push_back(*item);
						player->setActi(true); break;
					case 3: items.erase(items.begin() + i); //If it is an healing potion, the player gets 20 HP back
						player->setHealth(player->getHealth() + 20);
						if (player->getHealth() > 100) player->setHealth(100); break;
					default:break;
					}
				}

			}
		}

	}
	//Simple update of the buttons and the containers
	if (buttons.size() != 0) {
		for (int i = 0; i < buttons.size(); i++) buttons.at(i).update(0);
	}
	if (containers.size() != 0) {
		for (int i = 0; i < containers.size(); i++) containers.at(i).update(0);
	}
}

void Game::drawGame() {

	//Clear the rendering target
	SDL_RenderClear(renderer);
	//This is where we would add stuff to render;
	map->drawMap(widthscreen, heightscreen);
	if (!pause) {
		if (player != nullptr) player->drawGameObject();
		if (enemys.size() != 0) {
			for (int i = 0; i < enemys.size(); i++) enemys.at(i).drawGameObject();
		}
		if (attacks.size() != 0) {
			for (int i = 0; i < attacks.size(); i++) attacks.at(i).drawGameObject();
		}
		if (items.size() != 0) {
			for (int i = 0; i < items.size(); i++) items.at(i).drawGameObject();
		}
		if (boss != nullptr) boss->drawGameObject();
	}
	if (buttons.size() != 0) {
		for (int i = 0; i < buttons.size(); i++) buttons.at(i).drawGameObject();
	}

	if (containers.size() != 0) {
		for (int i = 0; i < containers.size(); i++) containers.at(i).drawGameObject();
	}
	//Update the screen
	SDL_RenderPresent(renderer);
}

void Game::destroyGame() {
	//Destroy the window
	SDL_DestroyWindow(window);
	//Destroy the renderer
	SDL_DestroyRenderer(renderer);
	//Destroy all the entities in case there are some remaining
	destroyAllEntities();
	//Destroy the subsystem
	SDL_Quit();
	std::cout << "The game is cleared" << std::endl;
}

void Game::destroyAllEntities() {
	//We simply destroy every entities that can be used during a game (player, enemies, attacks, ...)
	if (player != nullptr) {
		delete player;
		player = nullptr;
	}
	if (boss != nullptr) {
		delete boss;
		boss = nullptr;
	}
	if (enemys.size() != 0) {
		for (int i = 0; i < enemys.size(); i++)	enemys.erase(enemys.begin() + i);
		enemys.clear();
	}
	if (attacks.size() != 0) {
		for (int i = 0; i < attacks.size(); i++) attacks.erase(attacks.begin() + i);
		attacks.clear();
	}
	if (items.size() != 0) {
		for (int i = 0; i < items.size(); i++)	items.erase(items.begin() + i);
		items.clear();
	}
	if (containers.size() != 0) {
		for (int i = 0; i < containers.size(); i++)	containers.erase(containers.begin() + i);
		containers.clear();
	}

}

void Game::Pause() {
	//We set a frame during the user cannot use buttons
	timer();
	if (buttonFrame) {
		//If we are not on the mainMenu, the escape key will do something
		if (buttonType != 0) {
			//If we are in pause, we quit the pause, if we are not, we get in pause
			if (!pause) {
				pause = true;
				buttonType = 1;
				pauseButton = new Button("drawable/button_resume.gif", getScreenWidth() / 2 - 160, 256);
				mainMenu = new Button("drawable/button_main_menu.gif", getScreenWidth() / 2 - 160, 384);
				buttons.push_back(*pauseButton);
				buttons.push_back(*mainMenu);
				pause_logo = new Container("drawable/menu_logo.gif", getScreenWidth() / 2 - 225, 20, 225, 100);
				containers.push_back(*pause_logo);
			}
			else {
				pause = false;
				buttonType = 2;
				buttons.erase(buttons.begin());
				buttons.clear();
				containers.erase(containers.begin());
			}
			buttonFrame = false;
		}
	};
}

void Game::AddController(int id)
{
	if (SDL_IsGameController(id)) {
		// If the added device is a controller, we open it.
		pad = SDL_GameControllerOpen(id);
		if (pad) {
			// If the pad is openned, we take its joystick and give him an instance ID.
			SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
			int instanceID = SDL_JoystickInstanceID(joy);

			// We have to map the controller. Each controller have a different mapping.
			// Mapping Source : https://github.com/gabomdq/SDL_GameControllerDB
			SDL_GameControllerAddMappingsFromFile("controller_mapping/gamecontrollerdb_205");
			std::cout << "Controller Added" << std::endl;
		}
	}
}

void Game::RemoveController(int id)
{
	// When the controller is removed, we simply close it.
	SDL_GameControllerClose(pad);
	pad = NULL;
	std::cout << "Controller Removed" << std::endl;
}

void Game::OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent) {

	if (player != nullptr) {
		if (sdlEvent.axis == 0) {
			// X Axis motion (Right or Left axis motion)
			if (sdlEvent.value < -DEAD_ZONE) {
				std::cout << "X Axis Moved Left" << std::endl;
				// LEFT MOVEMENT.
				player->move(2);
			}
			else if (sdlEvent.value > DEAD_ZONE) {
				std::cout << "X Axis Moved Right" << std::endl;
				// RIGHT Movement.
				player->move(3);
			}
			else {
				player->stopMove();
			}
		}
		else if (sdlEvent.axis == 1) {
			// Y Axis motion (Up or Down axis motion)
			if (sdlEvent.value < -DEAD_ZONE) {
				std::cout << "Y Axis Moved Up" << std::endl;
				// UP ? Movement
				player->move(0);
			}
			else if (sdlEvent.value > DEAD_ZONE) {
				std::cout << "Y Axis Moved Down" << std::endl;
				player->move(1);
			}
			else {
				player->stopMove();
			}
		}
	}
}

void Game::OnControllerButton(const SDL_ControllerButtonEvent sdlEvent) {
	std::cout << "Button Pressed" << std::endl;
	if (player != nullptr) {
		switch (sdlEvent.button) {
		case SDL_CONTROLLER_BUTTON_Y:
			std::cout << sdlEvent.button << "Up Attack" << std::endl;
			attack(0);
			break;
		case SDL_CONTROLLER_BUTTON_A:
			std::cout << sdlEvent.button << "Down Attack" << std::endl;
			attack(1);
			break;
		case SDL_CONTROLLER_BUTTON_X:
			std::cout << sdlEvent.button << "Left Attack" << std::endl;
			attack(2);
			break;
		case SDL_CONTROLLER_BUTTON_B:
			std::cout << sdlEvent.button << "Right Attack" << std::endl;
			attack(3);
			break;
		case SDL_CONTROLLER_BUTTON_START:
			std::cout << "Pause Button" << std::endl;
			Pause();
			break;

		}
	}
}