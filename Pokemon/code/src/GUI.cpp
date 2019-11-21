#include "GUI.hpp"
#include "graphics.hpp"

#include <iostream>

GUI::~GUI() {
//	delete this->_textBox;
//	delete this->_menuBox;
//	delete this->_pokemonBag;
//	delete this->_fight;
}

GUI::GUI() {
	// this->_textBox = nullptr;
}

GUI::GUI(Graphics &graphics)
{
	this->_textBox = new TextBox(graphics);
	this->_menuBox = new MenuBox(graphics);
	this->_pokemonBag = new PokemonBag(graphics);
	this->_fight = new Fight(graphics);
}

void GUI::draw(Graphics &graphics, Player &player) {
	this->_textBox->draw(graphics);
	this->_menuBox->draw(graphics);
	// the order is important !!
	this->_pokemonBag->draw(graphics, player);
	this->_fight->draw(graphics, player);
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

Fight* GUI::getFight() {
	return this->_fight;
}
