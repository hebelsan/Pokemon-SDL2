/*
 * Fight.hpp
 *
 *  Created on: 21.04.2018
 *      Author: Alexander
 */

#ifndef FIGHT_HPP_
#define FIGHT_HPP_

#include "graphics.hpp"
#include "Fight/fightScene.hpp"

class Fight {
public:
	Fight();
	Fight(Graphics &graphics);
	void draw(Graphics &graphics, Player &player);

	void startFight();
private:
	FightScene *_fightScene;
};


#endif /* FIGHT_HPP_ */
