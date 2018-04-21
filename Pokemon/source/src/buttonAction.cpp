#include "buttonAction.hpp"
#include "btnActionHelper.hpp"
#include "input.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "level.hpp"
#include "GUI.hpp"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_image.h>

#include <iostream>

namespace btnAction {

	// handle Player movement
	void handleArrowKeys(Input &input, Player &player, GUI &gui) {

		// player can only walk if he's not talking
		if (gui.getTextBox()->isVisible()) {
			return;
		}
		if (gui.getFight()->isFighting()) {
			btnActionHelper::handleFightArrowKeys(player, gui);
			return;
		}

		// player should not walk if menu box is visible
		if (gui.getMenuBox()->visible() == true) {
			if (input.wasKeyPressed(SDL_SCANCODE_UP) == true) {
				gui.getMenuBox()->selectUp();
			}
			else if (input.wasKeyPressed(SDL_SCANCODE_DOWN) == true) {
				gui.getMenuBox()->selectDown();
			}
			return;
		}

		SDL_Scancode arrowKey = input.getPressedArrowKey();
		if (arrowKey == SDL_SCANCODE_UNKNOWN) {
			player.stopMoving();
		}
		else if (arrowKey == SDL_SCANCODE_LEFT) {
			player.moveLeft();
		}
		else if (arrowKey == SDL_SCANCODE_RIGHT) {
			player.moveRight();
		}
		else if (arrowKey == SDL_SCANCODE_UP) {
			player.moveUp();
		}
		else if (arrowKey == SDL_SCANCODE_DOWN) {
			player.moveDown();
		}
	}

	// handle EscapeKey
	void handleEscapeKey(Input &input) {
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			SDL_Quit();
			TTF_Quit();
			IMG_Quit();
			exit(0);
		}
	}

	// handle A Button
	void handleButtonA(Input &input, Level &level, Player &player, GUI &gui) {
		if (input.wasKeyPressed(SDL_SCANCODE_A) == true) {

			// handle menu interaction
			if (gui.getMenuBox()->visible() == true) {
				if (gui.getMenuBox()->getMenuItem() == MenuItem::POKEMON) {
					gui.getPokemonBag()->setVisible(true);
				}
				if (gui.getMenuBox()->getMenuItem() == MenuItem::BACK) {
					gui.getMenuBox()->setVisible(false);
				}
				return;
			}

			// first check if the player is already talking
			else if (gui.getTextBox()->isVisible()) {
				gui.getTextBox()->nextTextSection();
			}
			else if (gui.getFight()->isFighting()) {
				btnActionHelper::handleFightButtonA(level, player, gui);
			}
			else {
				btnActionHelper::handlePlayerTalking(level, player, gui);
				btnActionHelper::handleLevelItems(level, player, gui);
			}
		}
	}

	void handleButtonB(Input &input, GUI &gui) {
		// IF KEY WAS PRESSED
		if (input.wasKeyPressed(SDL_SCANCODE_S) == true) {
			if (gui.getPokemonBag()->visible()) {
				gui.getPokemonBag()->setVisible(false);
				return;
			}
			if (gui.getMenuBox()->visible()) {
				gui.getMenuBox()->setVisible(false);
				return;
			}
		}

	}

	void handleReturnKey(Input &input, GUI &gui) {
		// IF KEY WAS PRESSED
		if (input.wasKeyPressed(SDL_SCANCODE_RETURN) == true) {
			if (gui.getPokemonBag()->visible()) {
				gui.getPokemonBag()->setVisible(false);
				return;
			}
			gui.getMenuBox()->setVisible(!gui.getMenuBox()->visible());
		}
	}
}




