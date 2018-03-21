/*
 * GUI.hpp
 *
 *  Created on: 20.03.2018
 *      Author: Alexander
 */

#ifndef GUI_HPP_
#define GUI_HPP_

#include "textBox.hpp"

class Graphics;

class GUI {
public:
	~GUI();
	GUI();
	GUI(Graphics &graphics);
	void draw(Graphics &graphics);

	TextBox* getTextBox();
private:
	TextBox *_textBox;
};



#endif /* GUI_HPP_ */
