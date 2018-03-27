#include "pokemonBag.hpp"
#include "graphics.hpp"
#include "globals.hpp"

PokemonBag::~PokemonBag() {
	SDL_DestroyTexture(this->_backgroundTexture);
}

PokemonBag::PokemonBag() {}

PokemonBag::PokemonBag(Graphics &graphics) :
	_visible(false)
{
	this->_backgroundSrcRect.x = 0;
	this->_backgroundSrcRect.y = 0;
	this->_backgroundSrcRect.w = 240;
	this->_backgroundSrcRect.h = 160;

	this->_backgroundDstRect.x = 0;
	this->_backgroundDstRect.y = 0;
	this->_backgroundDstRect.w = globals::SCREEN_WIDTH;
	this->_backgroundDstRect.h = globals::SCREEN_HEIGHT;

	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonBag/Mock.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image menuBoxButton\n");
		printf(SDL_GetError());
	}
}

void PokemonBag::draw(Graphics &graphics) {
	if (this->_visible) {
		graphics.blitSurface(this->_backgroundTexture, &this->_backgroundSrcRect, &this->_backgroundDstRect);
	}
}

bool PokemonBag::visible() const {
	return this->_visible;
}

void PokemonBag::setVisible(bool value) {
	this->_visible = value;
}

