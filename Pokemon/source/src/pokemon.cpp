#include "pokemon.hpp"
#include <time.h>
#include <iostream>

Pokemon::~Pokemon() {
}

Pokemon::Pokemon() :
	_name(""),
	_level(0),
	_expType(PokemonExpTyp::UNKNOWN),
	_pokedexNumber(0),
	_currentKP(0),
	_kp(0),
	_atk(0),
	_spcAtk(0),
	_def(0),
	_spcDef(0),
	_init(0),
	_b_kp(0),
	_b_atk(0),
	_b_spcAtk(0),
	_b_def(0),
	_b_spcDef(0),
	_b_init(0),
	_fp_kp(0),
	_fp_atk(0),
	_fp_spcAtk(0),
	_fp_def(0),
	_fp_spcDef(0),
	_fp_init(0)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	srand((time_t)ts.tv_nsec);
	int dvRand = (rand() % 31) + 1;
	int sexRand = (rand() % 4) + 1; // number 1 <= x <= 4

	if(sexRand <= 2) {
		// feminin
		_sex = 'f';
	} else {
		// masculin
		_sex = 'm';
	}

	// random number from 0 to 31
	_dv_kp = dvRand;
	_dv_atk = dvRand;
	_dv_spcAtk = dvRand;
	_dv_def = dvRand;
	_dv_spcDef = dvRand;
	_dv_init = dvRand;

	// TODO Wesen im Moment alle 1.0
	_w_kp = 1.0;
	_w_atk = 1.0;
	_w_spcAtk = 1.0;
	_w_def = 1.0;
	_w_spcDef = 1.0;
	_w_init = 1.0;
}

void Pokemon::setLevel(int level) {
	this->_level = level;

	// kp is special
	this->_kp = ((((float)2 * _b_kp + _dv_kp + (_fp_kp / (float)4)) * _level) / 100) + _level + 10;

	this->_atk = ((((float)2 * _b_atk + _dv_atk + (_fp_atk / (float)4) * _level) / 100) + 5) * _w_atk;
	this->_def = ((((float)2 * _b_def + _dv_def + (_fp_def / (float)4) * _level) / 100) + 5) * _w_def;
	this->_spcAtk = ((((float)2 * _b_spcAtk + _dv_spcAtk + (_fp_spcAtk / (float)4) * _level) / 100) + 5) * _w_spcAtk;
	this->_spcDef = ((((float)2 * _b_spcDef + _dv_spcDef + (_fp_spcDef / (float)4) * _level) / 100) + 5) * _w_spcDef;
	this->_init = ((((float)2 * _b_init + _dv_init + (_fp_init / (float)4) * _level) / 100) + 5) * _w_init;
}

std::string Pokemon::getName() {
	return this->_name;
}

int Pokemon::getLevel() {
	return this->_level;
}

char Pokemon::getSex() {
	return this->_sex;
}

PokemonExpTyp Pokemon::getExpType() {
	return this->_expType;
}

int Pokemon::getPokedexNumber() {
	return this->_pokedexNumber;
}

int Pokemon::getCurrentHealth() {
	return this->_currentKP;
}

int Pokemon::getKP() {
	return this->_kp;
}

int Pokemon::getPhysicAttack() {
	return this->_atk;
}

int Pokemon::getSpecialAttack() {
	return this->_spcAtk;
}

int Pokemon::getPhysicDefence() {
	return this->_def;
}

int Pokemon::getSpecialDefence() {
	return this->_spcDef;
}

int Pokemon::getInitiative() {
	return this->_init;
}

Endivie::Endivie(int level) :
	Pokemon()
{
	this->_name = "Endivie";
	this->_pokedexNumber = 152;

	this->_expType = PokemonExpTyp::MITTEL_LANGSAM;

	// set basisWerte
	this->_b_kp = 45;
	this->_b_atk = 49;
	this->_b_def = 65;
	this->_b_spcAtk = 49;
	this->_b_spcDef = 65;
	this->_b_init = 45;

	this->setLevel(level);
	this->_currentKP = this->_kp;
}

Feurigel::Feurigel(int level) :
	Pokemon()
{
	this->_name = "Feurigel";
	this->_pokedexNumber = 155;

	this->_expType = PokemonExpTyp::MITTEL_LANGSAM;

	// set basisWerte
	this->_b_kp = 39;
	this->_b_atk = 52;
	this->_b_def = 43;
	this->_b_spcAtk = 60;
	this->_b_spcDef = 50;
	this->_b_init = 65;

	this->setLevel(level);
}

Karnimani::Karnimani(int level) :
	Pokemon()
{
	this->_name = "Karnimani";
	this->_pokedexNumber = 158;

	this->_expType = PokemonExpTyp::MITTEL_LANGSAM;

	// set basisWerte
	this->_b_kp = 50;
	this->_b_atk = 65;
	this->_b_def = 64;
	this->_b_spcAtk = 44;
	this->_b_spcDef = 48;
	this->_b_init = 43;

	this->setLevel(level);
}


