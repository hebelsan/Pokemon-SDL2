#include "Fight/fightScene.hpp"
#include "graphics.hpp"
#include "player.hpp"
#include "globals.hpp"
#include "font.hpp"
#include "PokemonTypeConverter.hpp"

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

	this->_playersPokemonSrcRect = {0,0,0,0};
	this->_playersPokemonDstRect = {0,0,0,0};

	this->_playersPokemonTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/Pokemon/thirdGenerationBack.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image Pokemons Back\n");
	}
}

void FightScene::draw(Graphics &graphics, Player &player, fight::FightStatus fightStatus,
		fight::NavMainItems navMainItem, fight::AttackItems attackItem, Pokemon &playerActivePokemon, Pokemon &enemyActivePokemon) {
	if (this->_visible) {
		graphics.blitSurface(this->_backgroundTexture, &this->_backgroundSrcRect, &this->_backgroundDstRect);
		drawMainNav(graphics, fightStatus);
		drawAttackSelection(graphics, fightStatus, playerActivePokemon, attackItem);
		drawNavigationArrow(graphics, player, fightStatus, navMainItem, attackItem);
		drawPokemons(graphics, playerActivePokemon, enemyActivePokemon);
	}
}

void FightScene::drawMainNav(Graphics &graphics, fight::FightStatus &fightStatus) {
	if (fightStatus == fight::FightStatus::NAVMAIN) {
		graphics.blitSurface(this->_mainNavigationTexture, &this->_mainNavSrcRect, &this->_mainNavDstRect);
	}
}

void FightScene::drawAttackSelection(Graphics &graphics, fight::FightStatus &fightStatus,
		Pokemon &playerActivePokemon, fight::AttackItems attackItem) {
	if (fightStatus == fight::FightStatus::SELECTATTACK) {
		graphics.blitSurface(this->_attackSelectBoxTexture, &this->_attackSelectBoxSrcRect, &this->_attackSelectBoxDstRect);

		if (playerActivePokemon.getAttacken().size() > 0) {
			drawAttackSelectionHelper(graphics, playerActivePokemon, 0, 42, 390);
		}
		if (playerActivePokemon.getAttacken().size() > 1) {
			drawAttackSelectionHelper(graphics, playerActivePokemon, 1, 240, 390);
		}
		if (playerActivePokemon.getAttacken().size() > 2) {
			drawAttackSelectionHelper(graphics, playerActivePokemon, 2, 42, 430);
		}
		if (playerActivePokemon.getAttacken().size() > 3) {
			drawAttackSelectionHelper(graphics, playerActivePokemon, 3, 240, 430);
		}

		// Draw Attack info
		switch(attackItem) {
			case fight::AttackItems::TL:
				drawAttackInfo(graphics, playerActivePokemon, 0);
				break;
			case fight::AttackItems::TR:
				drawAttackInfo(graphics, playerActivePokemon, 1);
				break;
			case fight::AttackItems::BL:
				drawAttackInfo(graphics, playerActivePokemon, 2);
				break;
			case fight::AttackItems::BR:
				drawAttackInfo(graphics, playerActivePokemon, 3);
				break;
		}
	}
}

void FightScene::drawAttackSelectionHelper(Graphics &graphics, Pokemon &playerActivePokemon, int attackIndex, int posX, int posY) {
	this->_fontSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(28),
						playerActivePokemon.getAttacken().at(attackIndex).getName().c_str(), Font::colorBlack(), 100);
	this->_fontTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_fontSurface);
	int txtWidth;
	int txtHeight;
	SDL_QueryTexture(this->_fontTexture, NULL, NULL, &txtWidth, &txtHeight);
	SDL_Rect sourceRect = {0, 0, txtWidth, txtHeight};
	SDL_Rect fontDestinationRectangle = { posX, posY,
			txtWidth/2 * (int)globals::SPRITE_SCALE,
			txtHeight/2 * (int)globals::SPRITE_SCALE};
	graphics.blitSurface(this->_fontTexture, &sourceRect, &fontDestinationRectangle);
}

void FightScene::drawAttackInfo(Graphics &graphics, Pokemon &playerActivePokemon, int attackIndex) {
	int ap = playerActivePokemon.getAttacken().at(attackIndex).getAp();
	int apMax = playerActivePokemon.getAttacken().at(attackIndex).getApMax();
	std::string leftAp = std::to_string(ap) + "/" + std::to_string(apMax);
	std::string typ = "Type/" + PokemonTypeConverter::pokemonTypToString(
			playerActivePokemon.getAttacken().at(attackIndex).getTyp());

	this->_fontSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(28),
			"AP", Font::colorBlack(), 100);
	this->_fontTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_fontSurface);
	int txtWidth;
	int txtHeight;
	SDL_QueryTexture(this->_fontTexture, NULL, NULL, &txtWidth, &txtHeight);
	SDL_Rect sourceRect = {0, 0, txtWidth, txtHeight};
	SDL_Rect fontDestinationRectangle = { 450, 390,
			txtWidth/2 * (int)globals::SPRITE_SCALE,
			txtHeight/2 * (int)globals::SPRITE_SCALE};
	graphics.blitSurface(this->_fontTexture, &sourceRect, &fontDestinationRectangle);

	this->_fontSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(28),
			leftAp.c_str(), Font::colorBlack(), 100);
	this->_fontTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_fontSurface);
	txtWidth;
	txtHeight;
	SDL_QueryTexture(this->_fontTexture, NULL, NULL, &txtWidth, &txtHeight);
	sourceRect = {0, 0, txtWidth, txtHeight};
	fontDestinationRectangle = { 550, 390,
			txtWidth/2 * (int)globals::SPRITE_SCALE,
			txtHeight/2 * (int)globals::SPRITE_SCALE};
	graphics.blitSurface(this->_fontTexture, &sourceRect, &fontDestinationRectangle);

	this->_fontSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(28),
						typ.c_str(), Font::colorBlack(), 100);
	this->_fontTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_fontSurface);
	txtWidth;
	txtHeight;
	SDL_QueryTexture(this->_fontTexture, NULL, NULL, &txtWidth, &txtHeight);
	sourceRect = {0, 0, txtWidth, txtHeight};
	fontDestinationRectangle = { 450, 430,
			txtWidth/2 * (int)globals::SPRITE_SCALE,
			txtHeight/2 * (int)globals::SPRITE_SCALE};
	graphics.blitSurface(this->_fontTexture, &sourceRect, &fontDestinationRectangle);
}

void FightScene::drawNavigationArrow(Graphics &graphics, Player &player,
		fight::FightStatus fightStatus, fight::NavMainItems navMainItem, fight::AttackItems attackItem) {
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
	} else if (fightStatus == fight::FightStatus::SELECTATTACK) {
		switch(attackItem) {
			case fight::AttackItems::TL:
				_selectArrowDstRect.x = 20;
				_selectArrowDstRect.y = 390;
				break;
			case fight::AttackItems::TR:
				_selectArrowDstRect.x = 218;
				_selectArrowDstRect.y = 390;
				break;
			case fight::AttackItems::BL:
				_selectArrowDstRect.x = 20;
				_selectArrowDstRect.y = 430;
				break;
			case fight::AttackItems::BR:
				_selectArrowDstRect.x = 218;
				_selectArrowDstRect.y = 430;
				break;
		}
	}
	graphics.blitSurface(this->_selectArrowTexture, &this->_selectArrowSrcRect, &this->_selectArrowDstRect);
}

void FightScene::drawPokemons(Graphics &graphics, Pokemon &playerActivePokemon, Pokemon &enemyActivePokemon) {
	// Draw players pokemon
	float scaleFactor = 2.5;
	int pokedexNumber = playerActivePokemon.getPokedexNumber();
	int x = ((pokedexNumber - 1) % 25) * 64;
	int y = ((pokedexNumber - 1) / 25) * 64;
	_playersPokemonSrcRect = {x, y, 64, 64};
	_playersPokemonDstRect = {100, 225, 64 * scaleFactor, 64 * scaleFactor};
	graphics.blitSurface(this->_playersPokemonTexture, &_playersPokemonSrcRect, &_playersPokemonDstRect);
}

bool FightScene::visible() const {
	return this->_visible;
}

void FightScene::setVisible(bool value) {
	this->_visible = value;
}




