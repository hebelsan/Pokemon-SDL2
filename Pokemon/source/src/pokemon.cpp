#include "pokemon.hpp"
#include <time.h>
#include <iostream>

Pokemon::~Pokemon() {
}

Pokemon::Pokemon() :
	_name(""),
	_level(0),
	_expType(PokemonExpTyp::UNKNOWN),
	_typ(PokemonTyp::UNKNOWNTYPE),
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

PokemonTyp Pokemon::getTyp() {
	return this->_typ;
}

int Pokemon::getPokedexNumber() {
	return this->_pokedexNumber;
}

std::vector<Attacken> Pokemon::getAttacken(){
	return this->_attacken;
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

void Pokemon::initiateAttacksHelper(std::vector<Attacken> &attacken,
			std::multimap <int, Attacken> &lernbareAttacken, int level) {
	std::vector<Attacken> attacks;
	for (auto const& x : lernbareAttacken)
	{
		if (x.first <= level) {
			attacks.push_back(x.second);
		}
	}

	if (attacks.size() <= 4) {
		for (unsigned int i = 0; i < attacks.size(); i++)
		{
			attacken.push_back(attacks.at(i));
		}
	}
	else {
		std::set<int> memoryNumbers;
		int indexRand = 0;
		bool isIn;
		for (int i = 0; i < 4; i++)
		{
			do {
			struct timespec ts;
			clock_gettime(CLOCK_MONOTONIC, &ts);
			srand((time_t)ts.tv_nsec);
			indexRand = (rand() % attacks.size()); // number 0 - attackSize - 1
			isIn = memoryNumbers.find(indexRand) != memoryNumbers.end();
			} while(isIn);
			memoryNumbers.insert(indexRand);
			attacken.push_back(attacks.at(indexRand));
		}
	}
}

Endivie::Endivie(int level) :
	Pokemon()
{
	this->_name = "Endivie";
	this->_pokedexNumber = 152;

	this->_expType = PokemonExpTyp::MITTEL_LANGSAM;
	this->_typ = PokemonTyp::PFLANZE;

	// set basisWerte
	this->_b_kp = 45;
	this->_b_atk = 49;
	this->_b_def = 65;
	this->_b_spcAtk = 49;
	this->_b_spcDef = 65;
	this->_b_init = 45;

	this->_lernbareAttacken.insert(std::pair<int, Attacken>(1, Tackle()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(1, Heuler()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(6, Rasierblatt()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(9, Giftpuder()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(12, Synthese()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(17, Reflektor()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(20, Zauberblatt()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(23, Beerenkraefte()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(28, Lockduft()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(31, Lichtschild()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(34, Bodyslam()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(39, Bodyguard()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(42, Aromakur()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(45, Solarstrahl()));
	this->setLevel(level);
	this->initiateAttacksHelper(_attacken, _lernbareAttacken, level);

	this->_currentKP = this->_kp;
}

Feurigel::Feurigel(int level) :
	Pokemon()
{
	this->_name = "Feurigel";
	this->_pokedexNumber = 155;

	this->_expType = PokemonExpTyp::MITTEL_LANGSAM;
	this->_typ = PokemonTyp::FEUER;

	// set basisWerte
	this->_b_kp = 39;
	this->_b_atk = 52;
	this->_b_def = 43;
	this->_b_spcAtk = 60;
	this->_b_spcDef = 50;
	this->_b_init = 65;

	this->_lernbareAttacken.insert(std::pair<int, Attacken>(1, Tackle()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(1, Silberblick()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(6, Rauchwolke()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(10, Glut()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(13, Ruckzuckhieb()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(19, Flammenrad()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(22, Einigler()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(28, Nitroladung()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(31, Sternschauer()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(37, Flammensturm()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(40, Flammenwurf()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(46, Inferno()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(49, Walzer()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(55, Risikotackle()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(58, Ausbrennen()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(64, Eruption()));
	this->setLevel(level);
	this->initiateAttacksHelper(_attacken, _lernbareAttacken, level);

	this->_currentKP = this->_kp;
}

Karnimani::Karnimani(int level) :
	Pokemon()
{
	this->_name = "Karnimani";
	this->_pokedexNumber = 158;

	this->_expType = PokemonExpTyp::MITTEL_LANGSAM;
	this->_typ = PokemonTyp::WASSER;

	// set basisWerte
	this->_b_kp = 50;
	this->_b_atk = 65;
	this->_b_def = 64;
	this->_b_spcAtk = 44;
	this->_b_spcDef = 48;
	this->_b_init = 43;

	this->_lernbareAttacken.insert(std::pair<int, Attacken>(1, Kratzer()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(1, Silberblick()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(6, Aquaknarre()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(10, Raserei()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(13, Biss()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(15, Grimasse()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(20, Eiszahn()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(22, Dreschflegel()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(27, Knirscher()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(29, Zermuerben()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(34, Schlitzer()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(36, Kreideschrei()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(41, Fuchtler()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(43, Nassschweif()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(48, Kraftkoloss()));
	this->_lernbareAttacken.insert(std::pair<int, Attacken>(50, Hydropumpe()));
	this->setLevel(level);
	this->initiateAttacksHelper(_attacken, _lernbareAttacken, level);

	this->_currentKP = this->_kp;
}


