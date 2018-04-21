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
		printf("\nError: Unable to load image fighting map\n");
	}

	this->_mainNavSrcRect.x = 0;
	this->_mainNavSrcRect.y = 0;
	this->_mainNavSrcRect.w = 473;
	this->_mainNavSrcRect.h = 186;

	this->_mainNavDstRect.x = globals::SCREEN_WIDTH - 250;
	this->_mainNavDstRect.y = globals::SCREEN_HEIGHT - 120;
	this->_mainNavDstRect.w = 250;
	this->_mainNavDstRect.h = 120;

	this->_mainNavigationTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/mainNavigation.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image mainNavigation fightScene\n");
	}

	this->_selectArrowSrcRect.x = 0;
	this->_selectArrowSrcRect.y = 0;
	this->_selectArrowSrcRect.w = 28;
	this->_selectArrowSrcRect.h = 44;

	this->_selectArrowDstRect = {0,0,0,0};

	this->_selectArrowTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/navigationButton.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image FightScene NavigationButton\n");
	}
}

void FightScene::draw(Graphics &graphics, Player &player, fight::FightStatus fightStatus, fight::NavMainItems navMainItem) {
	if (this->_visible) {
		graphics.blitSurface(this->_backgroundTexture, &this->_backgroundSrcRect, &this->_backgroundDstRect);
		graphics.blitSurface(this->_mainNavigationTexture, &this->_mainNavSrcRect, &this->_mainNavDstRect);
		drawNavigationArrow(graphics, player, fightStatus, navMainItem);
	}
}

void FightScene::drawNavigationArrow(Graphics &graphics, Player &player, fight::FightStatus fightStatus, fight::NavMainItems navMainItem) {

}

bool FightScene::visible() const {
	return this->_visible;
}

void FightScene::setVisible(bool value) {
	this->_visible = value;
}




