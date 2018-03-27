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

class PokemonBag{
public:
	~PokemonBag();
	PokemonBag();
	PokemonBag(Graphics &graphics);
	void draw(Graphics &graphics);

	bool visible() const;
	void setVisible(bool value);
private:
	bool _visible;

	SDL_Rect _backgroundSrcRect;
	SDL_Rect _backgroundDstRect;
	SDL_Texture* _backgroundTexture;
};



#endif /* POKEMONBAG_HPP_ */
