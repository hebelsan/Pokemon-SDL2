/*
 * textBox.hpp
 *
 *  Created on: 17.03.2018
 *      Author: Alexander
 */

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "sprite.hpp"

class Graphics;

class TextBox {
public:
	~TextBox();
	TextBox();
	TextBox(Graphics &graphics);
	void draw(Graphics &graphics);

	bool isVisible() const;
	void setVisible(bool value);

	void nextTextSection();

	// void setNpcText()
private:
	// textBox Position
	int textBoxPosX;
	int textBoxPosY;
	int textBoxWidth;
	int textBoxHeight;

	// text Position
	int txtPosX;
	int txtPosY;
	int txtWidth;
	int txtHeight;

	SDL_Color _fontColor;

	bool _visible;

	std::vector<std::string> _textSections;
	int _sectionCounter;

	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	SDL_Texture* _fontTexture;
	SDL_Surface* _fontSurface;
	TTF_Font* _font;
};



#endif /* TEXTBOX_HPP_ */
