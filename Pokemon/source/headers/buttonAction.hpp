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

namespace btnAction {
	void handleArrowKeys(Input &input, Player &player);
	void handleEscapeKey(Input &input);
	void handleButtonA(Input &input, Level &level, Player &player);
};



#endif /* BUTTONACTION_HPP_ */
