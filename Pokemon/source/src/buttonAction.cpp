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
		if (!gui.getTextBox()->isVisible()) {
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

			// first check if the player is already talking
			if (gui.getTextBox()->isVisible()) {
				gui.getTextBox()->nextTextSection();
			}
			else {

				std::vector<Npc*> levelNpcs = level.getNpcs();
				Direction playersDirection = player.getFacing();

				// loop each npc and check position to player
				for (int i = 0; i < levelNpcs.size(); i++) {
					switch (playersDirection) {
						case UP : {
							int playerPosTop = player.getBoundingBox().getTop();
							int npcPosBottom = levelNpcs.at(i)->getBoundingBox().getBottom();
							if (playerPosTop - npcPosBottom == 1 || playerPosTop - npcPosBottom == 0) {
								levelNpcs.at(i)->setFacing(DOWN);

								player.playAnimation("IdleUp");
								gui.getTextBox()->setVisible(true);
							}
							break;
						}
						case DOWN : {
							int playerPosBottom = player.getBoundingBox().getBottom();
							int npcPosTop = levelNpcs.at(i)->getBoundingBox().getTop();
							if (playerPosBottom - npcPosTop == -1 || playerPosBottom - npcPosTop == 0) {
								levelNpcs.at(i)->setFacing(UP);

								player.playAnimation("IdleDown");
								gui.getTextBox()->setVisible(true);
							}
							break;
						}
						case LEFT : {
							int playerPosLeft = player.getBoundingBox().getLeft();
							int npcPosRight = levelNpcs.at(i)->getBoundingBox().getRight();
							if (playerPosLeft - npcPosRight == 1 || playerPosLeft - npcPosRight == 0) {
								levelNpcs.at(i)->setFacing(RIGHT);

								player.playAnimation("IdleLeft");
								gui.getTextBox()->setVisible(true);
							}
							break;
						}
						case RIGHT : {
							int playerPosRight = player.getBoundingBox().getRight();
							int npsPosLeft = levelNpcs.at(i)->getBoundingBox().getLeft();
							if (playerPosRight - npsPosLeft == -1 || playerPosRight - npsPosLeft == 0) {
								levelNpcs.at(i)->setFacing(LEFT);

								player.playAnimation("IdleRight");
								gui.getTextBox()->setVisible(true);
							}
							break;
						}
					}
				}
			}
		}
	}

}



