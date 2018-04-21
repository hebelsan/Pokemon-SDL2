#include "Fight/fight.hpp"

Fight::Fight() {}

Fight::Fight(Graphics &graphics) {
	this->_fightScene = new FightScene(graphics);
	_mainNavItemsIndex = 0;
}

void Fight::draw(Graphics &graphics, Player &player) {
	this->_fightScene->draw(graphics, player, _status, getNavMainItem());
}

void Fight::startFight() {
	this->_fightScene->setVisible(true);
}

void Fight::endFight() {
	this->_fightScene->setVisible(false);
}

bool Fight::isFighting() {
	return this->_fightScene->visible();
}

void Fight::setStatus(fight::FightStatus status) {
	this->_status = status;
}

fight::FightStatus Fight::getStatus() {
	return this->_status;
}

void Fight::selectUp() {

}

void Fight::selectDown() {

}

void Fight::selectLeft() {

}

void Fight::selectRight() {

}

fight::NavMainItems Fight::getNavMainItem() {
	return _mainNavigationItems[_mainNavItemsIndex];
}
