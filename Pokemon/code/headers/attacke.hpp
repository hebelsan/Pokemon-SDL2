/*
 * attacken.hpp
 *
 *  Created on: 15.04.2018
 *      Author: Alexander
 */

#ifndef ATTACKE_HPP_
#define ATTACKE_HPP_

#include <string>
#include "globals.hpp"

class Attacke{
public:
	Attacke();

	int getAccuracy() const;
	int getAp() const;
	int getApMax() const;
	int getId() const;
	const std::string& getName() const;
	SchadensKlasse getSchadensKlasse() const;
	int getStrength() const;
	PokemonTyp getTyp() const;
	bool hasSpeedBonus() const;

	void reduceAp();
protected:
	int _id;
	std::string _name;
	PokemonTyp _typ;
	SchadensKlasse _schadensKlasse;
	int _strength;
	int _accuracy;
	int _ap;
	int _apMax;
	bool _hasEffect;
	bool _speedBonus;
};

class Pfund : public Attacke {
public:
	Pfund();
};

class Kratzer : public Attacke {
public:
	Kratzer();
};

class Tackle : public Attacke {
public:
	Tackle();
};

class Bodyslam : public Attacke {
public:
	Bodyslam();
};

class Fuchtler : public Attacke {
public:
	Fuchtler();
};

class Risikotackle : public Attacke {
public:
	Risikotackle();
};

class Silberblick : public Attacke {
public:
	Silberblick();
};

class Biss : public Attacke {
public:
	Biss();
};

class Heuler : public Attacke {
public:
	Heuler();
};

class Glut : public Attacke {
public:
	Glut();
};

class Flammenwurf : public Attacke {
public:
	Flammenwurf();
};

class Aquaknarre : public Attacke {
public:
	Aquaknarre();
};

class Hydropumpe : public Attacke {
public:
	Hydropumpe();
};

class Rasierblatt : public Attacke {
public:
	Rasierblatt();
};

class Solarstrahl : public Attacke {
public:
	Solarstrahl();
};

class Giftpuder : public Attacke {
public:
	Giftpuder();
};

class Ruckzuckhieb : public Attacke {
public:
	Ruckzuckhieb();
};

class Raserei : public Attacke {
public:
	Raserei();
};

class Kreideschrei : public Attacke {
public:
	Kreideschrei();
};

class Rauchwolke : public Attacke {
public:
	Rauchwolke();
};

class Einigler : public Attacke {
public:
	Einigler();
};

class Lichtschild : public Attacke {
public:
	Lichtschild();
};

class Reflektor : public Attacke {
public:
	Reflektor();
};

class Sternschauer : public Attacke {
public:
	Sternschauer();
};

class Schlitzer : public Attacke {
public:
	Schlitzer();
};

class Flammenrad : public Attacke {
public:
	Flammenrad();
};

class Dreschflegel : public Attacke {
public:
	Dreschflegel();
};

class Grimasse : public Attacke {
public:
	Grimasse();
};

class Walzer : public Attacke {
public:
	Walzer();
};

class Bodyguard : public Attacke {
public:
	Bodyguard();
};

class Lockduft : public Attacke {
public:
	Lockduft();
};

class Synthese : public Attacke {
public:
	Synthese();
};

class Knirscher : public Attacke {
public:
	Knirscher();
};

class Kraftkoloss : public Attacke {
public:
	Kraftkoloss();
};

class Eruption : public Attacke {
public:
	Eruption();
};

class Aromakur : public Attacke {
public:
	Aromakur();
};

class Zauberblatt : public Attacke {
public:
	Zauberblatt();
};

class Beerenkraefte : public Attacke {
public:
	Beerenkraefte();
};

class Nassschweif : public Attacke {
public:
	Nassschweif();
};

class Eiszahn : public Attacke {
public:
	Eiszahn();
};

class Flammensturm : public Attacke {
public:
	Flammensturm();
};

class Nitroladung : public Attacke {
public:
	Nitroladung();
};

class Zermuerben : public Attacke {
public:
	Zermuerben();
};

class Inferno : public Attacke {
public:
	Inferno();
};

class Ausbrennen : public Attacke {
public:
	Ausbrennen();
};

#endif /* ATTACKE_HPP_ */
