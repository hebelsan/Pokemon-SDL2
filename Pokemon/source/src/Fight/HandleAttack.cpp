#include "Fight/handleAttack.hpp"

HandleAttack::HandleAttack(FightTextBox* fightTextBox) {
	_state = AttackState::NOT_FIGHTING;
	this->_fightTextBox = fightTextBox;
}

void HandleAttack::startAttack(Pokemon &playersPokemon, Pokemon &enemysPokemon, int playersAttackIndex) {
	this->_playersPokemon = &playersPokemon;
	this->_enemysPokemon = &enemysPokemon;
	this->_playersAttack = &_playersPokemon->getAttacken().at(playersAttackIndex);
	this->_enemyAttack = calculateEnemiesAttack(enemysPokemon);

	std::cout << "pAttackDamage " << _playersAttack->getStrength() << std::endl;
	std::cout << "eAttackDamage " << _enemyAttack->getStrength() << std::endl;

	calculateInit();

	_state = AttackState::WRITE_FIRST_ATTACK;
	handleAttack();
}

void HandleAttack::handleAttack() {
	switch (_state) {
		case AttackState::WRITE_FIRST_ATTACK:
			{
				std::cout << "test2: " << getFirstAttack()->getStrength() << std::endl;

				std::string firstAttackString = getFirstAttackString();
				_fightTextBox->setText(firstAttackString);
				_state = AttackState::WRITE_FIRST_STATE_CHANGE;
			}
			break;
		case AttackState::WRITE_FIRST_STATE_CHANGE:
			{

				std::cout << "pAttackDamage " << _playersAttack->getStrength() << std::endl;
				std::cout << "eAttackDamage " << _enemyAttack->getStrength() << std::endl;
				// TODO check if state changes
				//if state does not change
				_state = AttackState::REDUCE_FIRST_HP;
				handleAttack();
			}
			break;
		case AttackState::REDUCE_FIRST_HP:
			{
				// TODO check if damage was done
				std::cout << "test1" << getFirstAttack()->getStrength();
				if(getFirstAttack()->getStrength() > 0) {
					_damage.handleDamage(getFirstPokemon(), getFirstAttack(), getSecondPokemon(), getFirstStufenSystem(), getSecondStufenSystem());
					_state = AttackState::CHECK_KO_FIRST;
				}
				else {
					_state = AttackState::CHECK_KO_FIRST;
					handleAttack();
				}
			}
			break;
		case AttackState::CHECK_KO_FIRST:
			{
				// TODO check if faster pokemon is dead
			}
			break;
		default:
			break;
	}
}

Attacke* HandleAttack::calculateEnemiesAttack(Pokemon &enemysPokemon) {
	int numberAttacks = enemysPokemon.getAttacken().size();
	// get random attack
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand((time_t)ts.tv_nsec);
	int attackRand = (rand() % numberAttacks); // number 0 <= x < numberAttacks Wenn size = 2 dann zwischen null und eins

	return &enemysPokemon.getAttacken().at(attackRand);
}

void HandleAttack::calculateInit() {
	// like ruckzuckhieb
	if (checkSpecialInitAttack()) {
		return;
	}
	if (_playersPokemon->getInitiative() > _enemysPokemon->getInitiative()) {
		_higherInit = HigherInit::PLAYER;
	}
	else if (_playersPokemon->getInitiative() < _enemysPokemon->getInitiative()) {
		_higherInit = HigherInit::ENEMY;
	}
	else if (_playersPokemon->getInitiative() == _enemysPokemon->getInitiative()) {
		switch (Random::flipCoin())
		{
			case true:
				_higherInit = HigherInit::PLAYER;
				break;
			case false:
				_higherInit = HigherInit::ENEMY;
				break;
		}
	}
}

// eg. checkRuckzuckieb
bool HandleAttack::checkSpecialInitAttack() {
	bool hasSpecialInitAttack = true;
	if (_playersAttack->hasSpeedBonus() && _enemyAttack->hasSpeedBonus()) {
		switch (Random::flipCoin())
			{
				case true:
					_higherInit = HigherInit::PLAYER;
					break;
				case false:
					_higherInit = HigherInit::ENEMY;
					break;
			}
	}
	else if (_playersAttack->hasSpeedBonus()) {
		_higherInit = HigherInit::PLAYER;
	}
	else if (_enemyAttack->hasSpeedBonus()) {
		_higherInit = HigherInit::ENEMY;
	}
	else {
		hasSpecialInitAttack = false;
	}
	return hasSpecialInitAttack;
}

std::string HandleAttack::getFirstAttackString() {
	std::string firstAttackString;
	switch(_higherInit)
	{
		case HigherInit::PLAYER:
			firstAttackString = _playersPokemon->getName() + " setzt " + _playersAttack->getName() + " ein.";
			break;
		case HigherInit::ENEMY:
			firstAttackString = _enemysPokemon->getName() + " setzt " + _enemyAttack->getName() + " ein.";
			break;
	}
	return firstAttackString;
}

void HandleAttack::resetPokemonsStufenSystem() {
	_playerStufenSystem.resetStufenSystem();
	_enemyStufenSystem.resetStufenSystem();
}

/*
 *
 * Private
 *
 */
Pokemon* HandleAttack::getFirstPokemon() {
	if(_higherInit == HigherInit::PLAYER)
		return _playersPokemon;
	else {
		return _enemysPokemon;
	}
}

Pokemon* HandleAttack::getSecondPokemon() {
	if(_higherInit == HigherInit::PLAYER)
		return _enemysPokemon;
	else {
		return _playersPokemon;
	}
}

Attacke* HandleAttack::getFirstAttack() {
	if(_higherInit == HigherInit::PLAYER) {
		return _playersAttack;
	} else {
		return _enemyAttack;
	}
}

Attacke* HandleAttack::getSecondAttack() {
	if(_higherInit == HigherInit::PLAYER) {
		return _enemyAttack;
	} else {
		return _playersAttack;
	}
}

StufenSystem& HandleAttack::getFirstStufenSystem() {
	if(_higherInit == HigherInit::PLAYER) {
		return _playerStufenSystem;
	} else {
		return _enemyStufenSystem;
	}
}

StufenSystem& HandleAttack::getSecondStufenSystem() {
	if(_higherInit == HigherInit::PLAYER) {
		return _enemyStufenSystem;
	} else {
		return _playerStufenSystem;
	}
}
