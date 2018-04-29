/*
 * FightScene.hpp
 *
 *  Created on: 21.04.2018
 *      Author: Alexander
 */

#ifndef FIGHTSCENE_HPP_
#define FIGHTSCENE_HPP_

#include "graphics.hpp"
#include "player.hpp"
#include "globals.hpp"

class FightScene {
public:
	~FightScene();
	FightScene();
	FightScene(Graphics &graphics);
	void draw(Graphics &graphics, Player &player, fight::FightStatus fightStatus,
			fight::NavMainItems navMainItem, fight::AttackItems attackItem, Pokemon &playerActivePokemon, Pokemon &enemyActivePokemon);
	void drawMainNav(Graphics &graphics, fight::FightStatus &fightStatus);
	void drawAttackSelection(Graphics &graphics, fight::FightStatus &fightStatus, Pokemon &playerActivePokemon, fight::AttackItems attackItem);
	void drawAttackSelectionHelper(Graphics &graphics, Pokemon &playerActivePokemon, int attackIndex, int posX, int posY);
	void drawAttackInfo(Graphics &graphics, Pokemon &playerActivePokemon, int attackIndex);
	void drawNavigationArrow(Graphics &graphics, Player &player, fight::FightStatus fightStatus, fight::NavMainItems navMainItem, fight::AttackItems attackItem);
	void drawPokemons(Graphics &graphics, Pokemon &playerActivePokemon, Pokemon &enemyActivePokemon);
	void drawPokemonsInfo(Graphics &graphics, Pokemon &playerActivePokemon, Pokemon &enemyActivePokemon);
	void drawPokemonsSex(Graphics &graphics, char sex, SDL_Rect &dstRect);
	void drawHealthBar(Graphics &graphics, int currentHealth, int maxHealth, SDL_Rect &dstRect);

	bool visible() const;
	void setVisible(bool value);
private:
	bool _visible;

	SDL_Rect _backgroundSrcRect;
	SDL_Rect _backgroundDstRect;
	SDL_Texture* _backgroundTexture;
	SDL_Rect _mainNavSrcRect;
	SDL_Rect _mainNavDstRect;
	SDL_Texture* _mainNavigationTexture;
	SDL_Rect _attackSelectBoxSrcRect;
	SDL_Rect _attackSelectBoxDstRect;
	SDL_Texture* _attackSelectBoxTexture;
	SDL_Rect _selectArrowSrcRect;
	SDL_Rect _selectArrowDstRect;
	SDL_Texture* _selectArrowTexture;

	/*
	 * Pokemons Textures
	 */
	float _pokemonScaleFactor;
	// players PokemonsTextures
	SDL_Rect _playersPokemonSrcRect;
	SDL_Rect _playersPokemonDstRect;
	SDL_Texture* _playersPokemonTexture;
	// enemies PokemonsTextures
	SDL_Rect _enemiesPokemonSrcRect;
	SDL_Rect _enemiesPokemonDstRect;
	SDL_Texture* _enemiesPokemonTexture;

	/*
	 * Pokemons Infos
	 */
	// players pokemonInfo
	SDL_Rect _playersPkmInfoSrcRect;
	SDL_Rect _playersPkmInfoDstRect;
	SDL_Texture* _playersPkmInfoTexture;
	// enemies pokemonInfo
	SDL_Rect _enemiesPkmInfoSrcRect;
	SDL_Rect _enemiesPkmInfoDstRect;
	SDL_Texture* _enemiesPkmInfoTexture;
	// Geschlecht texture
	SDL_Rect _playerSexDstRect;
	SDL_Rect _enemySexDstRect;

	SDL_Rect _masculinSrcRect;
	SDL_Texture* _masculinTexture;
	SDL_Rect _femininSrcRect;
	SDL_Texture* _femininTexture;
	// HealthBar
	SDL_Rect _playerHealtBarDstRect;
	SDL_Rect _enemyHealtBarDstRect;

	SDL_Rect _healthBarSrcRect;
	SDL_Texture* _healthBarGreenTexture;
	SDL_Texture* _healthBarOrangeTexture;
	SDL_Texture* _healthBarRedTexture;
};



#endif /* FIGHTSCENE_HPP_ */
