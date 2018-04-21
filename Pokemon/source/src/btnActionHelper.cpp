#include "btnActionHelper.hpp"
#include "input.hpp"
#include "player.hpp"
#include "npc.hpp"
#include "level.hpp"
#include "GUI.hpp"
#include "attacken.hpp"
#include "pokemonFactory.hpp"

#include <iostream>


namespace btnActionHelper {

	void handlePlayerTalking(Level &level, Player &player, GUI &gui) {
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

						if(levelNpcs.at(i)->getPokemons().size() > 0 ) {
							for (int k = 0; k < levelNpcs.at(i)->getPokemons().size(); k++) {
								std::cout << levelNpcs.at(i)->getPokemons().at(k).getName() << std::endl;
							}
							gui.getFight()->startFight();
						}
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
	}

	void handleLevelItems(Level &level, Player &player, GUI &gui) {
		Direction playersDirection = player.getFacing();

		// check Level Items
		for (unsigned int i = 0; i < level.getLevelItems().size(); i++) {

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
						player.addPokemon(PokemonFactory::createPokemon(level.getLevelItems().at(i).getItemAction(), 5));
						std::vector<Attacken> attacken = player.getPokemon(0).getAttacken();
						for (unsigned int i = 0; i < attacken.size(); i++) {
							std::cout << attacken.at(i).getName() << std::endl;
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

