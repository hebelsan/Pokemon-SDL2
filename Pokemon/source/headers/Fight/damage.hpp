/*
 * Damage.hpp
 *
 *  Created on: 02.05.2018
 *      Author: Alexander
 */

#ifndef FIGHT_DAMAGE_HPP_
#define FIGHT_DAMAGE_HPP_

#include "pokemon.hpp"
#include "Fight/stufenSystem.hpp"
#include "random.hpp"

#include <iostream>

class Damage{
public:
	void handleDamage(Pokemon* attackPkm, Attacke* attack, Pokemon* defPkm, StufenSystem &attackPkmStuSys, StufenSystem &defPkmStuSys) {
		std::cout << "attacke" << attack->getStrength() << std::endl;
		std::cout << "attacke" << attack->getName() << std::endl;



	/*
	 * Schaden=( (Level⋅(2/5)+2) * Basisschaden * ((Sp.)Angr / 50*(Sp.)Vert.) * ⋅F1+2) *Volltreffer*F2⋅(Z/100)*STAB*Typ1*Typ2*F3
	 */
		// (Level⋅(2/5)+2)
		int attackPkmLvl = attackPkm->getLevel();
		int levelDamage = attackPkmLvl * (2/5.0f) + 2;

		// basisSchaden = RH⋅BS⋅IT⋅LV⋅LS⋅NM⋅AF⋅ZF
		float rechteHand = 1.0f; // TODO check if unter einfluss von rechte Hand
		int base = attack->getStrength();

		float itemFaktor = 1.0f; // TODO itemfaktor
		float ladeVorgangFaktor = 1.0f; // TODO check if ladevorgang oder lehmsuhler
		float nassMacher = 1.0f; // TODO check nassmacher
		float af = 1.0f; // TODO fähigkeit des angreifers die den basiswert der attack verändern
		float zf = 1.0f; // TODO fähigkeit des verteidigers, die den angriff des angreifers verändert
		int basisSchaden = rechteHand * base * itemFaktor * ladeVorgangFaktor * nassMacher * af * zf;

		// (Sp.)Angr.=Stat⋅SV⋅FF⋅IF
		int statAttack = (attack->getSchadensKlasse() ==  SchadensKlasse::PHYSISCH) ? attackPkm->getPhysicAttack() : attackPkm->getSpecialAttack();
		float svAttack = (attack->getSchadensKlasse() ==  SchadensKlasse::PHYSISCH) ? attackPkmStuSys.getAtkFaktor() : attackPkmStuSys.getSpzAtkFaktor(); // TODO VOLTREFFER MIT EINBERECHNEN
		float ffAttack = 1.0; // TODO Fähigkeit einberechnen
		float ifAttack = 1.0; // TODO ItemFaktor einberechnen
		int finalAttack = statAttack * svAttack * ffAttack * ifAttack;

		// (Sp.)Vert.=Stat⋅SV⋅Mod⋅Ex
		int statDefense = (attack->getSchadensKlasse() ==  SchadensKlasse::PHYSISCH) ? defPkm->getPhysicDefence() : defPkm->getSpecialDefence();
		float svDefense = (attack->getSchadensKlasse() ==  SchadensKlasse::PHYSISCH) ? defPkmStuSys.getDefFaktor() : defPkmStuSys.getSpzDefFaktor();
		float modDefense = 1.0; // TODO spezielle Faktoren
		int finalDefense = statDefense * svDefense * modDefense;

		// F1 = BRT⋅RL⋅2V2⋅SR⋅FF
		float brt = 1.0; // TODO check if verbrennung -> dann 0.5 auf physische attacken
		float rl = 1.0; // TODO check if lichtschild oder reflektor aktiv
		float vs2 = 1.0; // TODO check if multikampf, wenn attacke 2 trifft dann ist 0.75
		float ff = 1.0; // TODO check Feuerfänger spezialfall
		int f1 = 1; // TODO richtig berechnen

		int f2 = 1; // TODO richtig berechnen
		int f3 = 1; // TODO richtig berechnen

		float stab = checkAttackAndPokemonSymeType(attackPkm, attack);

		float volltreffer = 1.0; // TODO calculate volltreffer !!!!

		int z = Random::calculateZ();

		float typ1 = 1.0; // TODO check effektivität der attack gegenüber gegnerischen typ
		float typ2 = 1.0; // TODO check effektivität der attack gegenüber gegnerischen typ


		int schaden = (levelDamage * basisSchaden * (finalAttack / (50.0f * finalDefense)) * f1 + 2) * volltreffer * f2 * (z / 100.0f) * stab * typ1 * typ2 * f3;

		// reduce ap of attack
		attack->reduceAp();
		// reduce enemies hp
		defPkm->setCurrenHealth(defPkm->getCurrentHealth() - schaden);
	}
private:
	float checkAttackAndPokemonSymeType(Pokemon *pokemon, Attacke *attack) {
		if (pokemon->getTyp() == attack->getTyp()) {
			return 1.5;
		} else {
			return 1.0;
		}
	}
};



#endif /* FIGHT_DAMAGE_HPP_ */
