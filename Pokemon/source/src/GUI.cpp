#include "GUI.hpp"
#include "graphics.hpp"

#include <iostream>

GUI::~GUI() {}

GUI::GUI() {
	// this->_textBox = nullptr;
}

GUI::GUI(Graphics &graphics)
{
	this->_textBox = new TextBox(graphics);
	this->_menuBox = new MenuBox(graphics);
	this->_pokemonBag = new PokemonBag(graphics);
}

void GUI::draw(Graphics &graphics) {
	this->_textBox->draw(graphics);
	this->_menuBox->draw(graphics);
	// the order is important !!
	this->_pokemonBag->draw(graphics);
}

TextBox* GUI::getTextBox() {
	return this->_textBox;
}

MenuBox* GUI::getMenuBox() {
	return this->_menuBox;
}

PokemonBag* GUI::getPokemonBag() {
	return this->_pokemonBag;
}


