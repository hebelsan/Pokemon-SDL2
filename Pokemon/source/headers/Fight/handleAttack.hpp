/*
 * handleAttack.hpp
 *
 *  Created on: 30.04.2018
 *      Author: Alexander
 */

#ifndef FIGHT_HANDLEATTACK_HPP_
#define FIGHT_HANDLEATTACK_HPP_

#include "pokemon.hpp"
#include "random.hpp"
#include "fightTextBox.hpp"

#include <string>
#include <iostream>

enum HigherInit {
	PLAYER,
	ENEMY
};

enum AttackState {
	NOT_FIGHTING,

	WRITE_FIRST_ATTACK, // calculate init, set Text for first attack
	WRITE_FIRST_STATE_CHANGE,
	REDUCE_FIRST_HP,
	WRITE_SECOND_ATTACK,
	WRITE_SECOND_STATE_CHANGE,
	REDUCE_SECOND_HP,
	// reduce AP -> then check if one Pokemon has <= 0 hp
	CHECK_END
};

class HandleAttack {
public:
	HandleAttack(FightTextBox* fightTextBox) {
		_state = AttackState::NOT_FIGHTING;
		this->_fightTextBox = fightTextBox;
	}

	void startAtack(Pokemon &playersPokemon, Pokemon &enemysPokemon, Attacke &playersAttack) {
		this->_playersPokemon = playersPokemon;
		this->_enemysPokemon = enemysPokemon;
		this->_playersAttack = playersAttack;
		this->_enemyAttack = calculateEnemiesAttack(enemysPokemon);

		calculateInit(playersPokemon, enemysPokemon);

		_state = AttackState::WRITE_FIRST_ATTACK;
		handleAttack();
	}

	void handleAttack() {
		switch (_state) {
			case AttackState::WRITE_FIRST_ATTACK:
				{
					std::string firstAttackString = getFirstAttackString();
					_fightTextBox->setText(firstAttackString);
					_state = AttackState::WRITE_FIRST_STATE_CHANGE;
				}
				break;
			case AttackState::WRITE_FIRST_STATE_CHANGE:
				{
					// TODO check if state changes
					//if state does not change
					_state = AttackState::REDUCE_FIRST_HP;
					handleAttack();
				}
				break;
			case AttackState::REDUCE_FIRST_HP:
				{
					// TODO check if damage was done
					std::cout << "damage" << std::endl;
					_playersPokemon.setCurrenHealth(_playersPokemon.getCurrentHealth() -_enemyAttack.getStrength());
				}
				break;
		}
	}

	Attacke& calculateEnemiesAttack(Pokemon &enemysPokemon) {
		int numberAttacks = enemysPokemon.getAttacken().size();
		// get random attack
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		srand((time_t)ts.tv_nsec);
		int attackRand = (rand() % numberAttacks); // number 0 <= x < numberAttacks Wenn size = 2 dann zwischen null und eins

		return enemysPokemon.getAttacken().at(attackRand);
	}

	void calculateInit(Pokemon &playersPokemon, Pokemon &enemysPokemon) {
		if (playersPokemon.getInitiative() > enemysPokemon.getInitiative()) {
			_higherInit = HigherInit::PLAYER;
		}
		else if (enemysPokemon.getInitiative() > playersPokemon.getInitiative()) {
			_higherInit = HigherInit::ENEMY;
		}
		else if (enemysPokemon.getInitiative() == playersPokemon.getInitiative()) {
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

	std::string getFirstAttackString() {
		std::string firstAttackString;
		switch(_higherInit)
		{
			case HigherInit::PLAYER:
				firstAttackString = _playersPokemon.getName() + " setzt " + _playersAttack.getName() + " ein.";
				break;
			case HigherInit::ENEMY:
				firstAttackString = _enemysPokemon.getName() + " setzt " + _enemyAttack.getName() + " ein.";
				break;
		}
		return firstAttackString;
	}
private:
	HigherInit _higherInit;
	AttackState _state;
	Pokemon _playersPokemon;
	Attacke _playersAttack;
	Pokemon _enemysPokemon;
	Attacke _enemyAttack;
	FightTextBox *_fightTextBox;
};



#endif /* FIGHT_HANDLEATTACK_HPP_ */
