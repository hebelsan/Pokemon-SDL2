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

class Graphics;

class GUI {
public:
	~GUI();
	GUI();
	GUI(Graphics &graphics);
	void draw(Graphics &graphics);

	TextBox* getTextBox();
	MenuBox* getMenuBox();
private:
	TextBox *_textBox;
	MenuBox *_menuBox;
};



#endif /* GUI_HPP_ */
