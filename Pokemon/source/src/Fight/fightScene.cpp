#include "Fight/fightScene.hpp"
#include "graphics.hpp"
#include "player.hpp"
#include "globals.hpp"
#include "font.hpp"

#include <iostream>

FightScene::~FightScene() {
	SDL_DestroyTexture(this->_backgroundTexture);
}

FightScene::FightScene() {}

FightScene::FightScene(Graphics &graphics) :
	_visible(false)
{
	this->_backgroundSrcRect.x = 0;
	this->_backgroundSrcRect.y = 0;
	this->_backgroundSrcRect.w = 240;
	this->_backgroundSrcRect.h = 112;

	this->_backgroundDstRect.x = 0;
	this->_backgroundDstRect.y = 0;
	this->_backgroundDstRect.w = globals::SCREEN_WIDTH;
	this->_backgroundDstRect.h = globals::SCREEN_HEIGHT - 120; // minus Textbox Height

	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/normalGrassMap.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image menuBoxButton\n");
	}
}

void FightScene::draw(Graphics &graphics, Player &player) {
	if (this->_visible) {
		graphics.blitSurface(this->_backgroundTexture, &this->_backgroundSrcRect, &this->_backgroundDstRect);
	}
}

bool FightScene::visible() const {
	return this->_visible;
}

void FightScene::setVisible(bool value) {
	this->_visible = value;
}




