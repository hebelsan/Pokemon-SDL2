/*
 * Fight.hpp
 *
 *  Created on: 21.04.2018
 *      Author: Alexander
 */

#ifndef FIGHT_HPP_
#define FIGHT_HPP_

#include "graphics.hpp"
#include "Fight/fightScene.hpp"
#include "globals.hpp"

class Fight {
public:
	Fight();
	Fight(Graphics &graphics);
	void draw(Graphics &graphics, Player &player);

	void startFight(const std::vector<Pokemon> &playerPokemon, const std::vector<Pokemon> &enemyPokemon);
	void endFight();
	bool isFighting();

	void setStatus(fight::FightStatus status);
	fight::FightStatus getStatus();

	void selectUpOrDown();
	void selectLeftOrRight();
	void pushA();
	void pushB();
	fight::NavMainItems getNavMainItem();
	void setNavMainItem(fight::NavMainItems navMainItem);

	Pokemon& getPlayersActivePokemon();
	Pokemon& getEnemysActivePokemon();
private:
	FightScene *_fightScene;
	fight::FightStatus _status;

	int _mainNavItemsIndex;
	fight::NavMainItems _mainNavigationItems[4] = {
			fight::NavMainItems::Kampf,
			fight::NavMainItems::Pokemon,
			fight::NavMainItems::Beutel,
			fight::NavMainItems::Flucht
	};
	std::vector<Pokemon> _playersPokemons;
	std::vector<Pokemon> _enemysPokemons;
	int _playersActivePokemon;
	int _enemysActivePokemon;
};


#endif /* FIGHT_HPP_ */
