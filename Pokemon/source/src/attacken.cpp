#include "attacken.hpp"

Attacken::Attacken() :
		_id(0),
		_name(""),
		_typ(PokemonTyp::UNKNOWNTYPE),
		_schadensKlasse(SchadensKlasse::UNKNOWNCLASS),
		_strength(0),
		_accuracy(0),
		_ap(0)
{
}

int Attacken::getAccuracy() const {
	return _accuracy;
}

int Attacken::getAp() const {
	return _ap;
}

int Attacken::getId() const {
	return _id;
}

const std::string& Attacken::getName() const {
	return _name;
}

SchadensKlasse Attacken::getSchadensKlasse() const {
	return _schadensKlasse;
}

int Attacken::getStrength() const {
	return _strength;
}

PokemonTyp Attacken::getTyp() const {
	return _typ;
}

/*
 *
 * Attacken
 *
 */

Pfund::Pfund() :
	Attacken()
{
	this->_id = 1;
	this->_name = "Pfund";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 40;
	this->_accuracy = 100;
	this->_ap = 35;
}

Kratzer::Kratzer() :
	Attacken()
{
	this->_id = 10;
	this->_name = "Kratzer";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 40;
	this->_accuracy = 100;
	this->_ap = 35;
}

Tackle::Tackle() :
	Attacken()
{
	this->_id = 33;
	this->_name = "Tackle";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 50;
	this->_accuracy = 100;
	this->_ap = 35;
}

Bodyslam::Bodyslam() :
	Attacken()
{
	this->_id = 34;
	this->_name = "Bodyslam";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 85;
	this->_accuracy = 100;
	this->_ap = 15;
}

Fuchtler::Fuchtler() :
	Attacken()
{
	this->_id = 37;
	this->_name = "Fuchtler";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 120;
	this->_accuracy = 100;
	this->_ap = 10;
}

Risikotackle::Risikotackle() :
	Attacken()
{
	this->_id = 38;
	this->_name = "Risikotackle";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 120;
	this->_accuracy = 100;
	this->_ap = 15;
}

Silberblick::Silberblick() :
	Attacken()
{
	this->_id = 43;
	this->_name = "Silberblick";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 100;
	this->_ap = 30;
}

Biss::Biss() :
	Attacken()
{
	this->_id = 44;
	this->_name = "Biss";
	this->_typ = PokemonTyp::UNLICHT;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 60;
	this->_accuracy = 100;
	this->_ap = 25;
}

Heuler::Heuler() :
	Attacken()
{
	this->_id = 45;
	this->_name = "Heuler";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 100;
	this->_ap = 40;
}

Glut::Glut() :
	Attacken()
{
	this->_id = 52;
	this->_name = "Glut";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 40;
	this->_accuracy = 100;
	this->_ap = 25;
}

Flammenwurf::Flammenwurf() :
	Attacken()
{
	this->_id = 53;
	this->_name = "Flammenwurf";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 90;
	this->_accuracy = 100;
	this->_ap = 15;
}

Aquaknarre::Aquaknarre() :
	Attacken()
{
	this->_id = 55;
	this->_name = "Aquaknarre";
	this->_typ = PokemonTyp::WASSER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 40;
	this->_accuracy = 100;
	this->_ap = 25;
}

Hydropumpe::Hydropumpe() :
	Attacken()
{
	this->_id = 56;
	this->_name = "Hydropumpe";
	this->_typ = PokemonTyp::WASSER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 110;
	this->_accuracy = 80;
	this->_ap = 5;
}

Rasierblatt::Rasierblatt() :
	Attacken()
{
	this->_id = 75;
	this->_name = "Rasierblatt";
	this->_typ = PokemonTyp::PFLANZE;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 55;
	this->_accuracy = 95;
	this->_ap = 25;
}

Solarstrahl::Solarstrahl() :
	Attacken()
{
	this->_id = 76;
	this->_name = "Solarstrahl";
	this->_typ = PokemonTyp::PFLANZE;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 120;
	this->_accuracy = 100;
	this->_ap = 10;
}

Giftpuder::Giftpuder() :
	Attacken()
{
	this->_id = 77;
	this->_name = "Giftpuder";
	this->_typ = PokemonTyp::GIFT;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 75;
	this->_ap = 35;
}

Ruckzuckhieb::Ruckzuckhieb() :
	Attacken()
{
	this->_id = 98;
	this->_name = "Ruckzuckhieb";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 40;
	this->_accuracy = 100;
	this->_ap = 30;
}

Raserei::Raserei() :
	Attacken()
{
	this->_id = 99;
	this->_name = "Raserei";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 20;
	this->_accuracy = 100;
	this->_ap = 20;
}

Kreideschrei::Kreideschrei() :
	Attacken()
{
	this->_id = 103;
	this->_name = "Kreideschrei";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 85;
	this->_ap = 40;
}

Rauchwolke::Rauchwolke() :
	Attacken()
{
	this->_id = 108;
	this->_name = "Rauchwolke";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 100;
	this->_ap = 20;
}

Einigler::Einigler() :
	Attacken()
{
	this->_id = 111;
	this->_name = "Einigler";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 0;
	this->_ap = 40;
}

Lichtschild::Lichtschild() :
	Attacken()
{
	this->_id = 113;
	this->_name = "Lichtschild";
	this->_typ = PokemonTyp::PSYCHO;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 0;
	this->_ap = 30;
}

Reflektor::Reflektor() :
	Attacken()
{
	this->_id = 115;
	this->_name = "Reflektor";
	this->_typ = PokemonTyp::PSYCHO;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 0;
	this->_ap = 20;
}

Sternschauer::Sternschauer() :
	Attacken()
{
	this->_id = 129;
	this->_name = "Sternschauer";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 60;
	this->_accuracy = -1;
	this->_ap = 20;
}

Schlitzer::Schlitzer() :
	Attacken()
{
	this->_id = 163;
	this->_name = "Schlitzer";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 70;
	this->_accuracy = 100;
	this->_ap = 20;
}

Flammenrad::Flammenrad() :
	Attacken()
{
	this->_id = 172;
	this->_name = "Flammenrad";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 60;
	this->_accuracy = 100;
	this->_ap = 25;
}

Dreschflegel::Dreschflegel() :
	Attacken()
{
	this->_id = 175;
	this->_name = "Dreschflegel";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 0;
	this->_accuracy = 100;
	this->_ap = 15;
}

Grimasse::Grimasse() :
	Attacken()
{
	this->_id = 184;
	this->_name = "Grimasse";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 100;
	this->_ap = 10;
}

Walzer::Walzer() :
	Attacken()
{
	this->_id = 205;
	this->_name = "Walzer";
	this->_typ = PokemonTyp::GESTEIN;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 30;
	this->_accuracy = 90;
	this->_ap = 20;
}


Bodyguard::Bodyguard() :
	Attacken()
{
	this->_id = 219;
	this->_name = "Bodyguard";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 0;
	this->_ap = 25;
}

Lockduft::Lockduft() :
	Attacken()
{
	this->_id = 230;
	this->_name = "Lockduft";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 100;
	this->_ap = 20;
}

Synthese::Synthese() :
	Attacken()
{
	this->_id = 235;
	this->_name = "Synthese";
	this->_typ = PokemonTyp::PFLANZE;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 0;
	this->_ap = 5;
}

Knirscher::Knirscher() :
	Attacken()
{
	this->_id = 242;
	this->_name = "Knirscher";
	this->_typ = PokemonTyp::UNLICHT;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 80;
	this->_accuracy = 100;
	this->_ap = 15;
}

Kraftkoloss::Kraftkoloss() :
	Attacken()
{
	this->_id = 276;
	this->_name = "Kraftkoloss";
	this->_typ = PokemonTyp::KAMPF;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 120;
	this->_accuracy = 100;
	this->_ap = 5;
}

Eruption::Eruption() :
	Attacken()
{
	this->_id = 284;
	this->_name = "Eruption";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = -1;
	this->_accuracy = 100;
	this->_ap = 5;
}

Aromakur::Aromakur() :
	Attacken()
{
	this->_id = 312;
	this->_name = "Aromakur";
	this->_typ = PokemonTyp::PFLANZE;
	this->_schadensKlasse = SchadensKlasse::STATUS;
	this->_strength = 0;
	this->_accuracy = 0;
	this->_ap = 5;
}

Zauberblatt::Zauberblatt() :
	Attacken()
{
	this->_id = 345;
	this->_name = "Zauberblatt";
	this->_typ = PokemonTyp::PFLANZE;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 60;
	this->_accuracy = -1;
	this->_ap = 20;
}

Beerenkraefte::Beerenkraefte() :
	Attacken()
{
	this->_id = 345;
	this->_name = "Beerenkräfte";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = -1;
	this->_accuracy = 100;
	this->_ap = 15;
}

Nassschweif::Nassschweif() :
	Attacken()
{
	this->_id = 401;
	this->_name = "Nassschweif";
	this->_typ = PokemonTyp::WASSER;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 90;
	this->_accuracy = 90;
	this->_ap = 10;
}

Eiszahn::Eiszahn() :
	Attacken()
{
	this->_id = 423;
	this->_name = "Eiszahn";
	this->_typ = PokemonTyp::EIS;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 65;
	this->_accuracy = 95;
	this->_ap = 15;
}

Flammensturm::Flammensturm() :
	Attacken()
{
	this->_id = 436;
	this->_name = "Flammensturm";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 80;
	this->_accuracy = 100;
	this->_ap = 15;
}

Nitroladung::Nitroladung() :
	Attacken()
{
	this->_id = 488;
	this->_name = "Nitroladung";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 50;
	this->_accuracy = 100;
	this->_ap = 20;
}

Zermuerben::Zermuerben() :
	Attacken()
{
	this->_id = 498;
	this->_name = "Zermürben";
	this->_typ = PokemonTyp::NORMAL;
	this->_schadensKlasse = SchadensKlasse::PHYSISCH;
	this->_strength = 70;
	this->_accuracy = 100;
	this->_ap = 20;
}

Inferno::Inferno() :
	Attacken()
{
	this->_id = 517;
	this->_name = "Inferno";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 100;
	this->_accuracy = 50;
	this->_ap = 5;
}

Ausbrennen::Ausbrennen() :
	Attacken()
{
	this->_id = 682;
	this->_name = "Ausbrennen";
	this->_typ = PokemonTyp::FEUER;
	this->_schadensKlasse = SchadensKlasse::SPEZIAL;
	this->_strength = 130;
	this->_accuracy = 100;
	this->_ap = 5;
}
