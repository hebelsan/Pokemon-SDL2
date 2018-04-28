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
	_visible(false),
	_pokemonScaleFactor(2.3)
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
	if (this->_mainNavigationTexture == NULL) {
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
	if (this->_attackSelectBoxTexture == NULL) {
		printf("\nError: Unable to load image attack Box\n");
	}

	this->_selectArrowSrcRect.x = 0;
	this->_selectArrowSrcRect.y = 0;
	this->_selectArrowSrcRect.w = 28;
	this->_selectArrowSrcRect.h = 44;

	this->_selectArrowDstRect = {0,0,14,22};

	this->_selectArrowTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/navigationButton.png"));
	if (this->_selectArrowTexture == NULL) {
		printf("\nError: Unable to load image FightScene NavigationButton\n");
	}

	this->_playersPokemonSrcRect = {0,0,0,0};
	this->_playersPokemonDstRect = {0,0,0,0};

	this->_playersPokemonTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/Pokemon/thirdGenerationBack.png"));
	if (this->_playersPokemonTexture == NULL) {
		printf("\nError: Unable to load image Pokemons Back\n");
	}

	this->_enemiesPokemonSrcRect = {0,0,0,0};
	this->_enemiesPokemonDstRect = {0,0,0,0};

	this->_enemiesPokemonTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/Pokemon/thirdGenerationFront.png"));
	if (this->_enemiesPokemonTexture == NULL) {
		printf("\nError: Unable to load image Pokemons front\n");
	}

	this->_playersPkmInfoSrcRect = {0,0,0,0};
	this->_playersPkmInfoDstRect = {0,0,0,0};

	this->_playersPkmInfoTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/playerInfo.png"));
	if (this->_playersPkmInfoTexture == NULL) {
		printf("\nError: Unable to load image players Pokemon info\n");
	}

	this->_enemiesPkmInfoSrcRect = {0,0,0,0};
	this->_enemiesPkmInfoDstRect = {0,0,0,0};

	this->_enemiesPkmInfoTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/enemyInfo.png"));
	if (this->_enemiesPkmInfoTexture == NULL) {
		printf("\nError: Unable to load enemies Pokemons info\n");
	}

	this->_masculinSrcRect = {0,0,29,34};
	this->_masculinDstRect = {385,315,19,24};

	this->_masculinTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/masculin.png"));
	if (this->_masculinTexture == NULL) {
		printf("\nError: Unable to load masculin sign BattleScene\n");
	}

	this->_femininSrcRect = {0,0,29,36};
	this->_femininDstRect = {385,315,19,24};

	this->_femininTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/feminin.png"));
	if (this->_masculinTexture == NULL) {
		printf("\nError: Unable to load feminin sign BattleScene\n");
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
	std::string attackName = playerActivePokemon.getAttacken().at(attackIndex).getName();

	Font::drawText(graphics, attackName, posX, posY, Font::getStandartFont(28), Font::colorBlack(), 100);
}

void FightScene::drawAttackInfo(Graphics &graphics, Pokemon &playerActivePokemon, int attackIndex) {
	int ap = playerActivePokemon.getAttacken().at(attackIndex).getAp();
	int apMax = playerActivePokemon.getAttacken().at(attackIndex).getApMax();
	std::string leftAp = std::to_string(ap) + "/" + std::to_string(apMax);
	std::string typ = "Type/" + PokemonTypeConverter::pokemonTypToString(
			playerActivePokemon.getAttacken().at(attackIndex).getTyp());

	Font::drawText(graphics, "AP", 450, 390, Font::getStandartFont(28), Font::colorBlack(), 100);

	Font::drawText(graphics, leftAp, 550, 390, Font::getStandartFont(28), Font::colorBlack(), 100);

	Font::drawText(graphics, typ, 450, 430, Font::getStandartFont(28), Font::colorBlack(), 100);
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
	int plyersPokedexNumber = playerActivePokemon.getPokedexNumber();
	int x = ((plyersPokedexNumber - 1) % 25) * 64;
	int y = ((plyersPokedexNumber - 1) / 25) * 64;
	_playersPokemonSrcRect = {x, y, 64, 64};
	_playersPokemonDstRect = {85, 213, (float)64 * _pokemonScaleFactor, (float)64 * _pokemonScaleFactor};
	graphics.blitSurface(this->_playersPokemonTexture, &_playersPokemonSrcRect, &_playersPokemonDstRect);

	// Draw enemies pokemon
	int enemiesPokedexNumber = enemyActivePokemon.getPokedexNumber();
	x = ((enemiesPokedexNumber - 1) % 25) * 64;
	y = ((enemiesPokedexNumber - 1) / 25) * 64;
	_enemiesPokemonSrcRect = {x, y, 64, 64};
	_enemiesPokemonDstRect = {400, 60, (float)64 * _pokemonScaleFactor, (float)64 * _pokemonScaleFactor};
	graphics.blitSurface(this->_enemiesPokemonTexture, &_enemiesPokemonSrcRect, &_enemiesPokemonDstRect);

	drawPokemonsInfo(graphics, playerActivePokemon, enemyActivePokemon);
}

void FightScene::drawPokemonsInfo(Graphics &graphics, Pokemon &playerActivePokemon, Pokemon &enemyActivePokemon) {
	// Draw players pokemon Info
	_playersPkmInfoSrcRect = {0, 0, 412, 144};
	_playersPkmInfoDstRect = {350, 245, 270, 110};
	graphics.blitSurface(this->_playersPkmInfoTexture, &_playersPkmInfoSrcRect, &_playersPkmInfoDstRect);

	std::string playersPkmName = playerActivePokemon.getName();
	std::string playersPkmLevel = "Lv." + std::to_string(playerActivePokemon.getLevel());

	Font::drawText(graphics, playersPkmName, 395, 260, Font::getStandartFont(28), Font::colorBlack(), 100);
	Font::drawText(graphics, playersPkmLevel, 545, 260, Font::getStandartFont(28), Font::colorBlack(), 100);
	if (playerActivePokemon.getSex() == 'm') {
		graphics.blitSurface(this->_masculinTexture, &_masculinSrcRect, &_masculinDstRect);
	} else if (playerActivePokemon.getSex() == 'f') {
		graphics.blitSurface(this->_femininTexture, &_femininSrcRect, &_femininDstRect);
	}

	// Draw enemies pokemon Info
	_enemiesPkmInfoSrcRect = {0, 0, 400, 112};
	_enemiesPkmInfoDstRect = {40, 50, 270, 80};
	graphics.blitSurface(this->_enemiesPkmInfoTexture, &_enemiesPkmInfoSrcRect, &_enemiesPkmInfoDstRect);
}

bool FightScene::visible() const {
	return this->_visible;
}

void FightScene::setVisible(bool value) {
	this->_visible = value;
}




