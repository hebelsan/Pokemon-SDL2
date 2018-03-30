#include "buttonAction.hpp"
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
			if (gui.getTextBox()->isVisible()) {
				gui.getTextBox()->nextTextSection();
			}
			else {

				std::vector<Npc*> levelNpcs = level.getNpcs();
				Direction playersDirection = player.getFacing();

				// loop each npc and check position to player
				for (unsigned int i = 0; i < levelNpcs.size(); i++) {
					switch (playersDirection) {
						case UP : {
							int playerPosTop = player.getBoundingBox().getTop();
							int playerXcenter = player.getBoundingBox().getCenterX();
							int npcPosBottom = levelNpcs.at(i)->getBoundingBox().getBottom();
							int npcPosLeft = levelNpcs.at(i)->getBoundingBox().getLeft();
							int npcWidth = levelNpcs.at(i)->getBoundingBox().getWidth();
							if ((playerPosTop - npcPosBottom == 1 || playerPosTop - npcPosBottom == 0) &&
									(playerXcenter  > npcPosLeft && playerXcenter < (npcPosLeft + npcWidth)))
							{
								levelNpcs.at(i)->setFacing(DOWN);

								player.playAnimation("IdleUp");
								gui.getTextBox()->setText(levelNpcs.at(i)->getText());
							}
							break;
						}
						case DOWN : {
							int playerPosBottom = player.getBoundingBox().getBottom();
							int playerXcenter = player.getBoundingBox().getCenterX();
							int npcPosTop = levelNpcs.at(i)->getBoundingBox().getTop();
							int npcPosLeft = levelNpcs.at(i)->getBoundingBox().getLeft();
							int npcWidth = levelNpcs.at(i)->getBoundingBox().getWidth();
							if ((playerPosBottom - npcPosTop == -1 || playerPosBottom - npcPosTop == 0) &&
									(playerXcenter  > npcPosLeft && playerXcenter < (npcPosLeft + npcWidth))) {
								levelNpcs.at(i)->setFacing(UP);

								player.playAnimation("IdleDown");
								gui.getTextBox()->setText(levelNpcs.at(i)->getText());
							}
							break;
						}
						case LEFT : {
							int playerPosLeft = player.getBoundingBox().getLeft();
							int playerYcenter = player.getBoundingBox().getCenterY();
							int npcPosRight = levelNpcs.at(i)->getBoundingBox().getRight();
							int npcPosTop = levelNpcs.at(i)->getBoundingBox().getTop();
							int npcHeight = levelNpcs.at(i)->getBoundingBox().getHeight();
							if ((playerPosLeft - npcPosRight == 1 || playerPosLeft - npcPosRight == 0) &&
									(playerYcenter > npcPosTop && playerYcenter < (npcPosTop + npcHeight))) {
								levelNpcs.at(i)->setFacing(RIGHT);

								player.playAnimation("IdleLeft");
								gui.getTextBox()->setText(levelNpcs.at(i)->getText());
							}
							break;
						}
						case RIGHT : {
							int playerPosRight = player.getBoundingBox().getRight();
							int playerYcenter = player.getBoundingBox().getCenterY();
							int npsPosLeft = levelNpcs.at(i)->getBoundingBox().getLeft();
							int npcPosTop = levelNpcs.at(i)->getBoundingBox().getTop();
							int npcHeight = levelNpcs.at(i)->getBoundingBox().getHeight();
							if ((playerPosRight - npsPosLeft == -1 || playerPosRight - npsPosLeft == 0) &&
									(playerYcenter > npcPosTop && playerYcenter < (npcPosTop + npcHeight))) {
								levelNpcs.at(i)->setFacing(LEFT);

								player.playAnimation("IdleRight");
								gui.getTextBox()->setText(levelNpcs.at(i)->getText());
							}
							break;
						}
					}
				}

				// check Level Items
				for (int i = 0; i < level.getLevelItems().size(); i++) {

					switch (playersDirection) {
						case UP : {
							int itemBot = level.getLevelItems().at(i).getBottom();
							int itemLeft = level.getLevelItems().at(i).getLeft();
							int itemWidth = level.getLevelItems().at(i).getWidth();
							int playerTop = player.getBoundingBox().getTop();
							int playerXcenter = player.getBoundingBox().getCenterX();
							if ((playerTop - itemBot) < 8 && (playerTop - itemBot) >= 0 &&
									(playerXcenter  > itemLeft && playerXcenter < (itemLeft + itemWidth))) {

								// TEST
								if (level.getLevelItems().at(i).getItemAction() == "endivie") {
									player.addPokemon(Endivie(5));
									Pokemon p = player.getPokemon(0);
									std::cout << "Kp: " << p.getKP() << std::endl;
									std::cout << "Init: " << p.getInitiative() << std::endl;
									std::cout << "atk: " << p.getPhysicAttack() << std::endl;
									std::cout << "def: " << p.getPhysicDefence() << std::endl;
									std::cout << "spcAtk: " << p.getSpecialAttack() << std::endl;
									std::cout << "spcDef: " << p.getSpecialDefence() << std::endl;
								}
								std::cout << level.getLevelItems().at(i).getItemAction() << std::endl;
							}
							break;
						}
						case DOWN : {
							int itemTop = level.getLevelItems().at(i).getTop();
							int itemLeft = level.getLevelItems().at(i).getLeft();
							int itemWidth = level.getLevelItems().at(i).getWidth();
							int playerBot = player.getBoundingBox().getBottom();
							int playerXcenter = player.getBoundingBox().getCenterX();
							if ((itemTop - playerBot) < 8 && (itemTop - playerBot) >= 0 &&
									(playerXcenter  > itemLeft && playerXcenter < (itemLeft + itemWidth))) {
								std::cout << level.getLevelItems().at(i).getItemAction() << std::endl;
							}
							break;
						}
						case LEFT : {
							int itemRight = level.getLevelItems().at(i).getRight();
							int itemTop = level.getLevelItems().at(i).getTop();
							int itemHeight = level.getLevelItems().at(i).getHeight();
							int playerLeft = player.getBoundingBox().getLeft();
							int playerYcenter = player.getBoundingBox().getCenterY();
							if ((playerLeft - itemRight) < 8 && (playerLeft - itemRight) > 0 &&
									(playerYcenter > itemTop && playerYcenter < (itemTop + itemHeight))) {
								std::cout << level.getLevelItems().at(i).getItemAction() << std::endl;
							}

							break;
						}
						case RIGHT : {
							int itemLeft = level.getLevelItems().at(i).getLeft();
							int itemTop = level.getLevelItems().at(i).getTop();
							int itemHeight = level.getLevelItems().at(i).getHeight();
							int playerRight = player.getBoundingBox().getRight();
							int playerYcenter = player.getBoundingBox().getCenterY();
							if ((itemLeft - playerRight) < 8 && (itemLeft - playerRight) > 0 &&
									(playerYcenter > itemTop && playerYcenter < (itemTop + itemHeight))) {
								std::cout << level.getLevelItems().at(i).getItemAction() << std::endl;
							}
							break;
						}
					}


				}
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




