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

	static void drawText(Graphics &graphics, std::string text, int x, int y, TTF_Font* font, SDL_Color color, int wrapLength) {
		SDL_Surface* fontSurface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, wrapLength);
		SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), fontSurface);
		int txtWidth;
		int txtHeight;
		SDL_QueryTexture(fontTexture, NULL, NULL, &txtWidth, &txtHeight);
		SDL_Rect sourceRect = {0, 0, txtWidth, txtHeight};
		SDL_Rect fontDestinationRectangle = { x, y,
				txtWidth/2 * (int)globals::SPRITE_SCALE,
				txtHeight/2 * (int)globals::SPRITE_SCALE};
		graphics.blitSurface(fontTexture, &sourceRect, &fontDestinationRectangle);
	}
};

#endif /* FONT_HPP_ */
