/*
 * attacken.hpp
 *
 *  Created on: 15.04.2018
 *      Author: Alexander
 */

#ifndef ATTACKEN_HPP_
#define ATTACKEN_HPP_

#include <string>
#include "globals.hpp"

class Attacken{
public:
	Attacken();

	int getAccuracy() const;
	int getAp() const;
	int getId() const;
	const std::string& getName() const;
	SchadensKlasse getSchadensKlasse() const;
	int getStrength() const;
	PokemonTyp getTyp() const;
protected:
	int _id;
	std::string _name;
	PokemonTyp _typ;
	SchadensKlasse _schadensKlasse;
	int _strength;
	int _accuracy;
	int _ap;
};

class Pfund : public Attacken {
public:
	Pfund();
};

class Kratzer : public Attacken {
public:
	Kratzer();
};

class Tackle : public Attacken {
public:
	Tackle();
};

class Bodyslam : public Attacken {
public:
	Bodyslam();
};

class Fuchtler : public Attacken {
public:
	Fuchtler();
};

class Risikotackle : public Attacken {
public:
	Risikotackle();
};

class Silberblick : public Attacken {
public:
	Silberblick();
};

class Biss : public Attacken {
public:
	Biss();
};

class Heuler : public Attacken {
public:
	Heuler();
};

class Glut : public Attacken {
public:
	Glut();
};

class Flammenwurf : public Attacken {
public:
	Flammenwurf();
};

class Aquaknarre : public Attacken {
public:
	Aquaknarre();
};

class Hydropumpe : public Attacken {
public:
	Hydropumpe();
};

class Rasierblatt : public Attacken {
public:
	Rasierblatt();
};

class Solarstrahl : public Attacken {
public:
	Solarstrahl();
};

class Giftpuder : public Attacken {
public:
	Giftpuder();
};

class Ruckzuckhieb : public Attacken {
public:
	Ruckzuckhieb();
};

class Raserei : public Attacken {
public:
	Raserei();
};

class Kreideschrei : public Attacken {
public:
	Kreideschrei();
};

class Rauchwolke : public Attacken {
public:
	Rauchwolke();
};

class Einigler : public Attacken {
public:
	Einigler();
};

class Lichtschild : public Attacken {
public:
	Lichtschild();
};

class Reflektor : public Attacken {
public:
	Reflektor();
};

class Sternschauer : public Attacken {
public:
	Sternschauer();
};

class Schlitzer : public Attacken {
public:
	Schlitzer();
};

class Flammenrad : public Attacken {
public:
	Flammenrad();
};

class Dreschflegel : public Attacken {
public:
	Dreschflegel();
};

class Grimasse : public Attacken {
public:
	Grimasse();
};

class Walzer : public Attacken {
public:
	Walzer();
};

class Bodyguard : public Attacken {
public:
	Bodyguard();
};

class Lockduft : public Attacken {
public:
	Lockduft();
};

class Synthese : public Attacken {
public:
	Synthese();
};

class Knirscher : public Attacken {
public:
	Knirscher();
};

class Kraftkoloss : public Attacken {
public:
	Kraftkoloss();
};

class Eruption : public Attacken {
public:
	Eruption();
};

class Aromakur : public Attacken {
public:
	Aromakur();
};

class Zauberblatt : public Attacken {
public:
	Zauberblatt();
};

class Beerenkraefte : public Attacken {
public:
	Beerenkraefte();
};

class Nassschweif : public Attacken {
public:
	Nassschweif();
};

class Eiszahn : public Attacken {
public:
	Eiszahn();
};

class Flammensturm : public Attacken {
public:
	Flammensturm();
};

class Nitroladung : public Attacken {
public:
	Nitroladung();
};

class Zermuerben : public Attacken {
public:
	Zermuerben();
};

class Inferno : public Attacken {
public:
	Inferno();
};

class Ausbrennen : public Attacken {
public:
	Ausbrennen();
};

#endif /* ATTACKEN_HPP_ */
