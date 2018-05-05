#include "Fight/fight.hpp"

#include "music.hpp"

Fight::Fight() {}

Fight::Fight(Graphics &graphics) {
	this->_fightScene = new FightScene(graphics);
	_attackHandler = new HandleAttack(_fightScene->getFightTextBox());
	_mainNavItemsIndex = 0;
	_attackItemsIndex = 0;
}

void Fight::draw(Graphics &graphics, Player &player) {
	if (isFighting()) {
		this->_fightScene->draw(graphics, player,
				_status, getNavMainItem(), getAttackItem(), getPlayersActivePokemon(), getEnemysActivePokemon());
	}
}

void Fight::startFight(std::vector<Pokemon> &playerPokemon, std::vector<Pokemon> &enemyPokemon) {
	this->_fightScene->setVisible(true);
	setStatus(fight::FightStatus::NAVMAIN);
	_mainNavItemsIndex = 0;
	this->_playersPokemons = &playerPokemon;
	this->_enemysPokemons = &enemyPokemon;
	this->_playersActivePokemon = 0;;
	this->_enemysActivePokemon = 0;

	_attackHandler->resetPokemonsStufenSystem();

	Music::getInstance()->fadeOut(30);
	Music::getInstance()->loadMusicFile("content/music/battle/Battle_Trainer.mp3");
	Music::getInstance()->play(-1);
}

void Fight::endFight() {
	this->_fightScene->setVisible(false);

	// TODO check map and play music depending on map
	Music::getInstance()->fadeOut(30);
	Music::getInstance()->loadMusicFile("content/music/LittlerootTown.mp3");
	Music::getInstance()->play(-1);
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
	else if (this->_status == fight::FightStatus::SELECTATTACK) {
		_status = fight::FightStatus::FIGHTING;
		_attackHandler->startAttack(getPlayersActivePokemon(), getEnemysActivePokemon(), _playersActivePokemon);
	}
	else if (this->_status == fight::FightStatus::FIGHTING) {
		// check if attack session finished
		if (_attackHandler->getAttackState() == AttackState::NOT_FIGHTING) {
			this->_status = fight::FightStatus::NAVMAIN;
			this->_fightScene->getFightTextBox()->setText("");
		}
		_attackHandler->handleAttack();
	}
}

void Fight::pushB() {
	if (this->_status == fight::FightStatus::SELECTATTACK) {
		setStatus(fight::FightStatus::NAVMAIN);
	} else if (this->_status == fight::FightStatus::FIGHTING) {
		_attackHandler->handleAttack();
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

Attacke& Fight::getPlayerActiveAttack() {
	return this->_playersPokemons->at(_playersActivePokemon).getAttacken().at(_attackItemsIndex);
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
	return this->_playersPokemons->at(_playersActivePokemon);
}

Pokemon& Fight::getEnemysActivePokemon() {
	return this->_enemysPokemons->at(_enemysActivePokemon);
}
