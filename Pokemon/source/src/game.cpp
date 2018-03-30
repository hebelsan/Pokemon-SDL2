#include "game.hpp"

#include "input.hpp"
#include "buttonAction.hpp"
#include "startScreen.hpp"
#include "music.hpp"

#include <SDL2/SDL.h>

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 100 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	Music music;
	SDL_Event event;

	StartScreen startScreen(graphics);
	startScreen.startStartScreenLoop(graphics, input, event, music);

	this->_level = Level("StartTown", graphics);
	this->_player = Player(graphics, this->_level.getPlayerSpawnPoint("start"));
	music.loadMusicFile("content/music/LittlerootTown.mp3");
	music.play(-1);

	this->_gui = GUI(graphics);

	int LAST_UPDATE_TIME = SDL_GetTicks();
	// start game loop
	while (true) {
		input.beginNewFrame();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		}

		// handle escape Key
		btnAction::handleEscapeKey(input);

		// handle return Key
		btnAction::handleReturnKey(input, this->_gui);

		// handle arrowKeys and players moving
		btnAction::handleArrowKeys(input, this->_player, this->_gui);

		// Handle A Button
		btnAction::handleButtonA(input, this->_level, this->_player, this->_gui);

		// Handle B Button
		btnAction::handleButtonB(input, this->_gui);

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->_graphics = graphics;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	this->_level.draw(graphics, this->_player.getCamera());
	this->_player.draw(graphics);
	this->_gui.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->_player.update(elapsedTime);
	this->_player.setCamera(this->_level.getMapWidth(), this->_level.getMapHeight());
	this->_level.update(elapsedTime, this->_player);

	// check collision
	std::vector<Rectangle> others;
	if ((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0) {
		// Player collied with at least one
		this->_player.handleTileCollisions(others);
	}
	// check slopes
	std::vector<Slope> otherSlopes;
	if ((otherSlopes = this->_level.checkSlopeCollisions(this->_player.getBoundingBox())).size() > 0) {
		this->_player.handleSlopeCollisions(otherSlopes);
	}
	// Check doors
	std::vector<Door> otherDoors;
	if ((otherDoors = this->_level.checkDoorCollisions(this->_player.getBoundingBox())).size() > 0) {
		this->_player.handleDoorCollision(otherDoors, this->_level, this->_graphics);
	}

	// Check npc collision
	std::vector<Npc*> otherNpcs;
	if ((otherNpcs = this->_level.checkNpcCollisions(this->_player.getBoundingBox())).size() > 0) {
		this->_player.handleNpcCollision(otherNpcs);
	}
}

