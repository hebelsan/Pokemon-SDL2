/*
 * buttonAction.hpp
 *
 *  Created on: 14.03.2018
 *      Author: Alexander
 */

#ifndef BUTTONACTION_HPP_
#define BUTTONACTION_HPP_

class Player;
class Input;
class Level;
class GUI;

namespace btnAction {
	void handleArrowKeys(Input &input, Player &player, GUI &gui);
	void handleEscapeKey(Input &input);
	void handleButtonA(Input &input, Level &level, Player &player, GUI &gui);
	void handleButtonB(Input &input, GUI &gui);
	void handleReturnKey(Input &input, GUI &gui);
};

#endif /* BUTTONACTION_HPP_ */
