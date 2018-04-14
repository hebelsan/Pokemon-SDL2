/*
 * pokemonBag.hpp
 *
 *  Created on: 26.03.2018
 *      Author: Alexander
 */

#ifndef POKEMONBAG_HPP_
#define POKEMONBAG_HPP_

#include <SDL2/SDL.h>

class Graphics;
class Player;

class PokemonBag{
public:
	~PokemonBag();
	PokemonBag();
	PokemonBag(Graphics &graphics);
	void draw(Graphics &graphics, Player &player);
	void drawPokemonStats(Graphics &graphics, Player &player);
	void drawSinglePokemonStat(Graphics & graphics, Player &player, int pkmBagNumber, int ballX, int ballY,
			int nameX, int nameY, int lvX, int lvY, int thumbNailX, int thumbNailY);

	bool visible() const;
	void setVisible(bool value);
private:
	bool _visible;

	SDL_Rect _backgroundSrcRect;
	SDL_Rect _backgroundDstRect;
	SDL_Texture* _backgroundTexture;
	SDL_Texture* _pokeBallTexture;
	SDL_Texture* _pokemonsTexture;
};



#endif /* POKEMONBAG_HPP_ */
