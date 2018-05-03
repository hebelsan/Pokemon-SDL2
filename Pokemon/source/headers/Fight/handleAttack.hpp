/*
 * handleAttack.hpp
 *
 *  Created on: 30.04.2018
 *      Author: Alexander
 */

#ifndef FIGHT_HANDLEATTACK_HPP_
#define FIGHT_HANDLEATTACK_HPP_

#include <Fight/damage.hpp>
#include "pokemon.hpp"
#include "random.hpp"
#include "fightTextBox.hpp"
#include "stufenSystem.hpp"
#include "damage.hpp"

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
	CHECK_KO_FIRST,
	WRITE_SECOND_ATTACK,
	WRITE_SECOND_STATE_CHANGE,
	REDUCE_SECOND_HP,
	CHECK_KO_SECOND, // reduce AP -> then check if one Pokemon has <= 0 hp
};

class HandleAttack {
public:
	HandleAttack(FightTextBox* fightTextBox);

	void startAttack(Pokemon &playersPokemon, Pokemon &enemysPokemon, int playersAttackIndex);

	void handleAttack();

	Attacke* calculateEnemiesAttack(Pokemon &enemysPokemon);

	void calculateInit();

	bool checkSpecialInitAttack(); // like ruckzuckhieb

	void resetPokemonsStufenSystem();
private:
	HigherInit _higherInit;
	AttackState _state;
	Pokemon* _playersPokemon;
	Attacke* _playersAttack;
	Pokemon* _enemysPokemon;
	Attacke* _enemyAttack;
	FightTextBox *_fightTextBox;

	StufenSystem _playerStufenSystem;
	StufenSystem _enemyStufenSystem;

	Damage _damage;

	std::string getFirstAttackString();
	Pokemon* getFirstPokemon();
	Pokemon* getSecondPokemon();
	Attacke* getFirstAttack();
	Attacke* getSecondAttack();
	StufenSystem& getFirstStufenSystem();
	StufenSystem& getSecondStufenSystem();
};



#endif /* FIGHT_HANDLEATTACK_HPP_ */
