/*
 * pokemon.hpp
 *
 *  Created on: 30.03.2018
 *      Author: Alexander
 */

#ifndef POKEMON_HPP_
#define POKEMON_HPP_

#include <attacke.hpp>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "globals.hpp"

class Pokemon {
public:
	~Pokemon();
	Pokemon();

	void setLevel(int level);
	void setCurrenHealth(int health);

	std::string getName();
	int getLevel();
	char getSex();
	PokemonExpTyp getExpType();
	PokemonTyp getTyp();
	int getPokedexNumber();
	std::vector<Attacke>& getAttacken();

	int getCurrentHealth();

	int getKP();
	int getPhysicAttack();
	int getSpecialAttack();
	int getPhysicDefence();
	int getSpecialDefence();
	int getInitiative();

	void initiateAttacksHelper(std::vector<Attacke> &attacken,
			std::multimap <int, Attacke> &lernbareAttacken, int level);
protected:
	std::string _name;
	int _level;
	char _sex;
	PokemonExpTyp _expType;
	PokemonTyp _typ;
	std::vector<Attacke> _attacken;
	std::multimap <int, Attacke> _lernbareAttacken;  // < level, attack>

	int _pokedexNumber;

	int _currentKP;

	// permanent attributes
	int _kp;
	int _atk;
	int _spcAtk;
	int _def;
	int _spcDef;
	int _init;

	// Basis Werte
	int _b_kp;
	int _b_atk;
	int _b_spcAtk;
	int _b_def;
	int _b_spcDef;
	int _b_init;

	// FP fleißpunkte max 510 FP
	int _fp_kp;
	int _fp_atk;
	int _fp_spcAtk;
	int _fp_def;
	int _fp_spcDef;
	int _fp_init;

	// DV determinant Value 0 - 31
	int _dv_kp;
	int _dv_atk;
	int _dv_spcAtk;
	int _dv_def;
	int _dv_spcDef;
	int _dv_init;

	// TODO Wesen im Moment alle 1.0
	float _w_kp;
	float _w_atk;
	float _w_spcAtk;
	float _w_def;
	float _w_spcDef;
	float _w_init;
};

class Endivie : public Pokemon {
public:
	Endivie(int level);
};

class Feurigel : public Pokemon {
public:
	Feurigel(int level);
};

class Karnimani : public Pokemon {
public:
	Karnimani(int level);
};

#endif /* POKEMON_HPP_ */
