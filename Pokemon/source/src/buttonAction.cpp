#include "buttonAction.hpp"
#include "input.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "level.hpp"

#include <iostream>

namespace btnAction {

	// handle Player movement
	void handleArrowKeys(Input &input, Player &player) {
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
			exit(0);
		}
	}

	// handle A Button
	void handleButtonA(Input &input, Level &level, Player &player) {
		if (input.wasKeyPressed(SDL_SCANCODE_A) == true) {

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

							player.getTextBox()->setVisible(true);
							std::cout << "textbox now visible" << std::endl;
						}
						break;
					}
					case DOWN : {
						int playerPosBottom = player.getBoundingBox().getBottom();
						int npcPosTop = levelNpcs.at(i)->getBoundingBox().getTop();
						if (playerPosBottom - npcPosTop == -1 || playerPosBottom - npcPosTop == 0) {
							levelNpcs.at(i)->setFacing(UP);
							std::cout << "text" << std::endl;
						}
						break;
					}
					case LEFT : {
						int playerPosLeft = player.getBoundingBox().getLeft();
						int npcPosRight = levelNpcs.at(i)->getBoundingBox().getRight();
						if (playerPosLeft - npcPosRight == 1 || playerPosLeft - npcPosRight == 0) {
							levelNpcs.at(i)->setFacing(RIGHT);
							std::cout << "text" << std::endl;
						}
						break;
					}
					case RIGHT : {
						int playerPosRight = player.getBoundingBox().getRight();
						int npsPosLeft = levelNpcs.at(i)->getBoundingBox().getLeft();
						if (playerPosRight - npsPosLeft == -1 || playerPosRight - npsPosLeft == 0) {
							levelNpcs.at(i)->setFacing(LEFT);
							std::cout << "text" << std::endl;
						}
						break;
					}
				}
			}
		}
	}

}



