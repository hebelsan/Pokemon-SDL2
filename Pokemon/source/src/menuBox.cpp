#include "menuBox.hpp"
#include "graphics.hpp"
#include "globals.hpp"

#include <iostream>

MenuBox::~MenuBox() {
	SDL_DestroyTexture(this->_menuBoxTexture);
}

MenuBox::MenuBox() {}

MenuBox::MenuBox(Graphics &graphics) :
	_visible(false),
	_menuItemsIndex(0)
{
	this->_menuBoxSourceRect.x = 0;
	this->_menuBoxSourceRect.y = 0;
	this->_menuBoxSourceRect.w = 160;
	this->_menuBoxSourceRect.h = 283;

	this->_menuBoxDestinationRect.x = globals::SCREEN_WIDTH - (int)globals::SPRITE_SCALE * _menuBoxWidth;
	this->_menuBoxDestinationRect.y = (globals::SCREEN_HEIGHT - (int)globals::SPRITE_SCALE * _menuBoxHeight) / 2;
	this->_menuBoxDestinationRect.w = this->_menuBoxWidth * (int)globals::SPRITE_SCALE;
	this->_menuBoxDestinationRect.h = this->_menuBoxHeight * (int)globals::SPRITE_SCALE;

	this->_menuBoxTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonMenu.png"));
	if (this->_menuBoxTexture == NULL) {
		printf("\nError: Unable to load image menuBox\n");
		printf(SDL_GetError());
	}

	this->_menuSelectorSourceRect.x = 0;
	this->_menuSelectorSourceRect.y = 0;
	this->_menuSelectorSourceRect.w = 12;
	this->_menuSelectorSourceRect.h = 20;

	this->_menuSelectorDestinationRect.x = globals::SCREEN_WIDTH - 164;
	this->_menuSelectorDestinationRect.y = 96;
	this->_menuSelectorDestinationRect.w = 6 * (int)globals::SPRITE_SCALE;
	this->_menuSelectorDestinationRect.h = 10 * (int)globals::SPRITE_SCALE;

	this->_menuSelectorTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonMenuButton.png"));
	if (this->_menuBoxTexture == NULL) {
		printf("\nError: Unable to load image menuBoxButton\n");
		printf(SDL_GetError());
	}

	// initialize MenuItemList
}

void MenuBox::draw(Graphics &graphics){
	if (this->_visible) {
		// Draw MenuBox
		graphics.blitSurface(this->_menuBoxTexture, &this->_menuBoxSourceRect, &this->_menuBoxDestinationRect);
		graphics.blitSurface(this->_menuSelectorTexture, &this->_menuSelectorSourceRect, &this->_menuSelectorDestinationRect);
	}
}

bool MenuBox::visible() const{
	return this->_visible;
}

void MenuBox::setVisible(bool value){
	this->_visible = value;
}

void MenuBox::selectUp() {
	if (_menuItemsIndex > 0) {
		this->_menuSelectorDestinationRect.y -= 38;
		this->_menuItemsIndex--;
	}
}

void MenuBox::selectDown() {
	// the menu has 8 entries
	if (_menuItemsIndex < 7) {
		this->_menuSelectorDestinationRect.y += 38;
		this->_menuItemsIndex++;
	}
}

MenuItem MenuBox::getMenuItem() {
	return this->_menuItemsArray[this->_menuItemsIndex];
}

