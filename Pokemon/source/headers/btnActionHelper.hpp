/*
 * btnActionHelper.hpp
 *
 *  Created on: 31.03.2018
 *      Author: Alexander
 */

#ifndef BTNACTIONHELPER_HPP_
#define BTNACTIONHELPER_HPP_

class Player;
class Input;
class Level;
class GUI;

namespace btnActionHelper {
	void handlePlayerTalking(Level &level, Player &player, GUI &gui);
	void handleLevelItems(Level &level, Player &player, GUI &gui);
	void handleFightButtonA(Level &level, Player &player, GUI &gui);
	void handleFightArrowKeys(Player &player, GUI &gui, Input &input);
};



#endif /* BTNACTIONHELPER_HPP_ */
