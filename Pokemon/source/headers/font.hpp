/*
 * font.hpp
 *
 *  Created on: 30.03.2018
 *      Author: Alexander
 */

#ifndef FONT_HPP_
#define FONT_HPP_

#include "SDL2/SDL_ttf.h"

class Font {
public:
	static TTF_Font* getStandartFont(int size) {
		return TTF_OpenFont("content/fonts/Pokemon_font.ttf", size);
	}
	static SDL_Color colorBlack() {
		SDL_Color color;
		color.r = 0;
		color.g = 0;
		color.b = 0;
		return color;
	}
	static SDL_Color colorWhite() {
		SDL_Color color;
		color.r = 255;
		color.g = 255;
		color.b = 255;
		return color;
	}
};

#endif /* FONT_HPP_ */
