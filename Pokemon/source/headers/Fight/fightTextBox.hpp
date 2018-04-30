/*
 * fightTextBox.hpp
 *
 *  Created on: 30.04.2018
 *      Author: Alexander
 */

#ifndef FIGHT_FIGHTTEXTBOX_HPP_
#define FIGHT_FIGHTTEXTBOX_HPP_

#include "graphics.hpp"

class FightTextBox {
public:
	FightTextBox(Graphics &graphics);
	void draw(Graphics &graphics);
	void setVisible(bool visible);
	void setText(std::string text);
private:
	bool _visible;
	std::string _text;
	SDL_Rect _textBoxSrcRect;
	SDL_Rect _textBoxDstRect;
	SDL_Texture* _textBoxTexture;
};


#endif /* FIGHT_FIGHTTEXTBOX_HPP_ */
