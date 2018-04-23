#include "Fight/fight.hpp"

Fight::Fight() {}

Fight::Fight(Graphics &graphics) {
	this->_fightScene = new FightScene(graphics);
	_mainNavItemsIndex = 0;
}

void Fight::draw(Graphics &graphics, Player &player) {
	if (isFighting()) {
		this->_fightScene->draw(graphics, player, _status, getNavMainItem(), getPlayersActivePokemon(), getEnemysActivePokemon());
	}
}

void Fight::startFight(const std::vector<Pokemon> &playerPokemon, const std::vector<Pokemon> &enemyPokemon) {
	this->_fightScene->setVisible(true);
	setStatus(fight::FightStatus::NAVMAIN);
	_mainNavItemsIndex = 0;
	this->_playersPokemons = playerPokemon;
	this->_enemysPokemons = enemyPokemon;
	this->_playersActivePokemon = 0;;
	this->_enemysActivePokemon = 0;
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

void Fight::selectUpOrDown() {
	if (this->_status == fight::FightStatus::NAVMAIN) {
		switch(getNavMainItem()) {
			case fight::NavMainItems::Kampf: setNavMainItem(fight::NavMainItems::Pokemon);
				break;
			case fight::NavMainItems::Pokemon: setNavMainItem(fight::NavMainItems::Kampf);
				break;
			case fight::NavMainItems::Beutel: setNavMainItem(fight::NavMainItems::Flucht);
				break;
			case fight::NavMainItems::Flucht: setNavMainItem(fight::NavMainItems::Beutel);
				break;
		}
	}
}

void Fight::selectLeftOrRight() {
	if (this->_status == fight::FightStatus::NAVMAIN) {
		switch(getNavMainItem()) {
			case fight::NavMainItems::Kampf: setNavMainItem(fight::NavMainItems::Beutel);
				break;
			case fight::NavMainItems::Beutel: setNavMainItem(fight::NavMainItems::Kampf);
				break;
			case fight::NavMainItems::Pokemon: setNavMainItem(fight::NavMainItems::Flucht);
				break;
			case fight::NavMainItems::Flucht: setNavMainItem(fight::NavMainItems::Pokemon);
				break;
		}
	}
}

void Fight::pushA() {
	if (this->_status == fight::FightStatus::NAVMAIN) {
		switch(getNavMainItem()) {
			case fight::NavMainItems::Kampf: setStatus(fight::FightStatus::SELECTATTACK);
				break;
			case fight::NavMainItems::Beutel: // TODO
				break;
			case fight::NavMainItems::Pokemon: // TODO
				break;
			case fight::NavMainItems::Flucht: endFight();
				break;
		}
	}
}

void Fight::pushB() {
	if (this->_status == fight::FightStatus::SELECTATTACK) {
		setStatus(fight::FightStatus::NAVMAIN);
	}
}

fight::NavMainItems Fight::getNavMainItem() {
	return _mainNavigationItems[_mainNavItemsIndex];
}

void Fight::setNavMainItem(fight::NavMainItems navMainItem) {
	if (navMainItem == fight::NavMainItems::Kampf) {
		_mainNavItemsIndex = 0;
	} else if (navMainItem == fight::NavMainItems::Pokemon) {
		_mainNavItemsIndex = 1;
	} else if (navMainItem == fight::NavMainItems::Beutel) {
		_mainNavItemsIndex = 2;
	} else if (navMainItem == fight::NavMainItems::Flucht) {
		_mainNavItemsIndex = 3;
	}
}

Pokemon& Fight::getPlayersActivePokemon() {
	return this->_playersPokemons.at(_playersActivePokemon);
}

Pokemon& Fight::getEnemysActivePokemon() {
	return this->_enemysPokemons.at(_enemysActivePokemon);
}
