#include "Fight/fight.hpp"

Fight::Fight() {}

Fight::Fight(Graphics &graphics) {
	this->_fightScene = new FightScene(graphics);
}

void Fight::draw(Graphics &graphics, Player &player) {
	this->_fightScene->draw(graphics, player);
}

void Fight::startFight() {
	this->_fightScene->setVisible(true);
}


