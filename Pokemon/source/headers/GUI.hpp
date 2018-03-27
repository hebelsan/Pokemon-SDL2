/*
 * GUI.hpp
 *
 *  Created on: 20.03.2018
 *      Author: Alexander
 */

#ifndef GUI_HPP_
#define GUI_HPP_

#include "textBox.hpp"
#include "menuBox.hpp"
#include "pokemonBag.hpp"

class Graphics;

class GUI {
public:
	~GUI();
	GUI();
	GUI(Graphics &graphics);
	void draw(Graphics &graphics);

	TextBox* getTextBox();
	MenuBox* getMenuBox();
	PokemonBag* getPokemonBag();
private:
	TextBox *_textBox;
	MenuBox *_menuBox;
	PokemonBag *_pokemonBag;
};



#endif /* GUI_HPP_ */
