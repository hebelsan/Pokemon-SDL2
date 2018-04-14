/*
 * textBox.hpp
 *
 *  Created on: 17.03.2018
 *      Author: Alexander
 */

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include <SDL2/SDL.h>
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
	void setText(std::string text);

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

	bool _visible;

	std::vector<std::string> _textSections;
	int _sectionCounter;

	SDL_Rect _sourceRect;
	SDL_Rect _textBoxDestinationRectangle;
	SDL_Texture* _textBoxTexture;
	SDL_Texture* _fontTexture;
	SDL_Surface* _fontSurface;
};



#endif /* TEXTBOX_HPP_ */
