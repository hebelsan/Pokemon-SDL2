#include "Fight/fight.hpp"

Fight::Fight() {}

Fight::Fight(Graphics &graphics) {
	this->_fightScene = new FightScene(graphics);
	_mainNavItemsIndex = 0;
	_attackItemsIndex = 0;
}

void Fight::draw(Graphics &graphics, Player &player) {
	if (isFighting()) {
		this->_fightScene->draw(graphics, player,
				_status, getNavMainItem(), getAttackItem(), getPlayersActivePokemon(), getEnemysActivePokemon());
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
	} else if (this->_status == fight::FightStatus::SELECTATTACK) {
		switch(getAttackItem()) {
			case fight::AttackItems::TL: setAttackItem(fight::AttackItems::BL);
				break;
			case fight::AttackItems::BL: setAttackItem(fight::AttackItems::TL);
				break;
			case fight::AttackItems::TR: setAttackItem(fight::AttackItems::BR);
				break;
			case fight::AttackItems::BR: setAttackItem(fight::AttackItems::TR);
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
	} else if (this->_status == fight::FightStatus::SELECTATTACK) {
		switch(getAttackItem()) {
			case fight::AttackItems::TL: setAttackItem(fight::AttackItems::TR);
				break;
			case fight::AttackItems::TR: setAttackItem(fight::AttackItems::TL);
				break;
			case fight::AttackItems::BR: setAttackItem(fight::AttackItems::BL);
				break;
			case fight::AttackItems::BL: setAttackItem(fight::AttackItems::BR);
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

fight::AttackItems Fight::getAttackItem() {
	return _attackItems[_attackItemsIndex];
}

void Fight::setAttackItem(fight::AttackItems attackItem) {
	int amountAttacks = getPlayersActivePokemon().getAttacken().size();
	if (attackItem == fight::AttackItems::TL) {
		_attackItemsIndex = 0;
	} else if (attackItem == fight::AttackItems::TR && amountAttacks > 1) {
		_attackItemsIndex = 1;
	} else if (attackItem == fight::AttackItems::BL && amountAttacks > 2) {
		_attackItemsIndex = 2;
	} else if (attackItem == fight::AttackItems::BR && amountAttacks > 3) {
		_attackItemsIndex = 3;
	}
}

Pokemon& Fight::getPlayersActivePokemon() {
	return this->_playersPokemons.at(_playersActivePokemon);
}

Pokemon& Fight::getEnemysActivePokemon() {
	return this->_enemysPokemons.at(_enemysActivePokemon);
}
