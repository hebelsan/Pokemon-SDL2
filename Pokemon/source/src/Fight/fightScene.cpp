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

	this->_attackSelectBoxSrcRect.x = 0;
	this->_attackSelectBoxSrcRect.y = 0;
	this->_attackSelectBoxSrcRect.w = 3114;
	this->_attackSelectBoxSrcRect.h = 689;

	this->_attackSelectBoxDstRect.x = 0;
	this->_attackSelectBoxDstRect.y = globals::SCREEN_HEIGHT - 120;
	this->_attackSelectBoxDstRect.w = globals::SCREEN_WIDTH;
	this->_attackSelectBoxDstRect.h = 120;

	this->_attackSelectBoxTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/attackSelectBox.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image attack Box\n");
	}

	this->_selectArrowSrcRect.x = 0;
	this->_selectArrowSrcRect.y = 0;
	this->_selectArrowSrcRect.w = 28;
	this->_selectArrowSrcRect.h = 44;

	this->_selectArrowDstRect = {0,0,14,22};

	this->_selectArrowTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/navigationButton.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image FightScene NavigationButton\n");
	}
}

void FightScene::draw(Graphics &graphics, Player &player, fight::FightStatus fightStatus, fight::NavMainItems navMainItem) {
	if (this->_visible) {
		graphics.blitSurface(this->_backgroundTexture, &this->_backgroundSrcRect, &this->_backgroundDstRect);
		drawMainNav(graphics, fightStatus);
		drawAttackSelection(graphics, fightStatus);
		drawNavigationArrow(graphics, player, fightStatus, navMainItem);
	}
}

void FightScene::drawMainNav(Graphics &graphics, fight::FightStatus &fightStatus) {
	if (fightStatus == fight::FightStatus::NAVMAIN) {
		graphics.blitSurface(this->_mainNavigationTexture, &this->_mainNavSrcRect, &this->_mainNavDstRect);
	}
}

void FightScene::drawAttackSelection(Graphics &graphics, fight::FightStatus &fightStatus) {
	if (fightStatus == fight::FightStatus::SELECTATTACK) {
		graphics.blitSurface(this->_attackSelectBoxTexture, &this->_attackSelectBoxSrcRect, &this->_attackSelectBoxDstRect);
	}
}

void FightScene::drawNavigationArrow(Graphics &graphics, Player &player, fight::FightStatus fightStatus, fight::NavMainItems navMainItem) {
	if (fightStatus == fight::FightStatus::NAVMAIN) {
		switch(navMainItem) {
			case fight::NavMainItems::Kampf:
				_selectArrowDstRect.x = globals::SCREEN_WIDTH - 235;
				_selectArrowDstRect.y = globals::SCREEN_HEIGHT - 90;
				break;
			case fight::NavMainItems::Pokemon:
				_selectArrowDstRect.x = globals::SCREEN_WIDTH - 235;
				_selectArrowDstRect.y = globals::SCREEN_HEIGHT - 49;
				break;
			case fight::NavMainItems::Beutel:
				_selectArrowDstRect.x = globals::SCREEN_WIDTH - 118;
				_selectArrowDstRect.y = globals::SCREEN_HEIGHT - 90;
				break;
			case fight::NavMainItems::Flucht:
				_selectArrowDstRect.x = globals::SCREEN_WIDTH - 118;
				_selectArrowDstRect.y = globals::SCREEN_HEIGHT - 49;
				break;
		}
		graphics.blitSurface(this->_selectArrowTexture, &this->_selectArrowSrcRect, &this->_selectArrowDstRect);
	}
}

bool FightScene::visible() const {
	return this->_visible;
}

void FightScene::setVisible(bool value) {
	this->_visible = value;
}




