#include "pokemonBag.hpp"
#include "graphics.hpp"
#include "player.hpp"
#include "globals.hpp"
#include "font.hpp"

#include <iostream>

PokemonBag::~PokemonBag() {
	SDL_DestroyTexture(this->_backgroundTexture);
	SDL_DestroyTexture(this->_pokeBallTexture);
	SDL_DestroyTexture(this->_healthBarTexture);
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

	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonBag/PokemonBag_raw.png"));
	if (this->_backgroundTexture == NULL) {
		printf("\nError: Unable to load image menuBoxButton\n");
	}
	this->_pokeBallTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonBag/Pokeball_Passive.png"));
	if (this->_pokeBallTexture == NULL) {
		printf("\nError: Unable to load image pokeBall\n");
	}
	this->_pokemonsTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/Pokemon/pokemonIcons.png"));
	if (this->_pokemonsTexture == NULL) {
		printf("\nError: Unable to load Pokemons Texture\n");
	}
	this->_healthBarTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonBag/healthBar.png"));
	if (this->_pokemonsTexture == NULL) {
		printf("\nError: Unable to load healthBar Texture\n");
	}
}

void PokemonBag::draw(Graphics &graphics, Player &player) {
	if (this->_visible) {
		graphics.blitSurface(this->_backgroundTexture, &this->_backgroundSrcRect, &this->_backgroundDstRect);
		this->drawPokemonStats(graphics, player);
	}
}

void PokemonBag::drawPokemonStats(Graphics &graphics, Player &player) {
	if (player.getNumberOfPokemons() > 0) {
		int pkmBagNumber = 0;
		int ballX = 6;
		int ballY = 62;
		int nameX = 85;
		int nameY = 125;
		int lvX = 95;
		int lvY = 147;
		int thumbNailX = 16;
		int thumbNailY = 90;
		int healthX = 145;
		int healthY = 200;
		int healthBarX = 85;
		int healthBarY = 182;

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY,
				lvX, lvY, thumbNailX, thumbNailY, healthX, healthY, healthBarX, healthBarY);
	}
	if (player.getNumberOfPokemons() > 1) {
		int pkmBagNumber = 1;
		int ballX = 232;
		int ballY = 33;
		int nameX = 325;
		int nameY = 47;
		int lvX = 325;
		int lvY = 69;
		int thumbNailX = 245;
		int thumbNailY = 42;
		int healthX = 550;
		int healthY = 70;
		int healthBarX = 488;
		int healthBarY = 53;

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY,
				lvX, lvY, thumbNailX, thumbNailY, healthX, healthY, healthBarX, healthBarY);
	}
	if (player.getNumberOfPokemons() > 2) {
		int pkmBagNumber = 2;
		int ballX = 232;
		int ballY = 105;
		int nameX = 325;
		int nameY = 120;
		int lvX = 325;
		int lvY = 142;
		int thumbNailX = 245;
		int thumbNailY = 115;
		int healthX = 550;
		int healthY = 142;
		int healthBarX = 488;
		int healthBarY = 125;

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY,
				lvX, lvY, thumbNailX, thumbNailY, healthX, healthY, healthBarX, healthBarY);
	}
	if (player.getNumberOfPokemons() > 3) {
		int pkmBagNumber = 3;
		int ballX = 232;
		int ballY = 177;
		int nameX = 325;
		int nameY = 192;
		int lvX = 325;
		int lvY = 214;
		int thumbNailX = 245;
		int thumbNailY = 187;
		int healthX = 550;
		int healthY = 214;
		int healthBarX = 488;
		int healthBarY = 197;

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY,
				lvX, lvY, thumbNailX, thumbNailY, healthX, healthY, healthBarX, healthBarY);
	}
	if (player.getNumberOfPokemons() > 4) {
		int pkmBagNumber = 4;
		int ballX = 232;
		int ballY = 249;
		int nameX = 325;
		int nameY = 264;
		int lvX = 325;
		int lvY = 286;
		int thumbNailX = 245;
		int thumbNailY = 259;
		int healthX = 550;
		int healthY = 286;
		int healthBarX = 488;
		int healthBarY = 269;

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY,
				lvX, lvY, thumbNailX, thumbNailY, healthX, healthY, healthBarX, healthBarY);
	}
	if (player.getNumberOfPokemons() > 5) {
		int pkmBagNumber = 5;
		int ballX = 232;
		int ballY = 321;
		int nameX = 325;
		int nameY = 336;
		int lvX = 325;
		int lvY = 358;
		int thumbNailX = 245;
		int thumbNailY = 331;
		int healthX = 550;
		int healthY = 358;
		int healthBarX = 488;
		int healthBarY = 341;

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY,
				lvX, lvY, thumbNailX, thumbNailY, healthX, healthY, healthBarX, healthBarY);
	}
}

void PokemonBag::drawSinglePokemonStat(Graphics & graphics, Player &player, int pkmBagNumber, int ballX, int ballY,
			int nameX, int nameY, int lvX, int lvY, int thumbNailX, int thumbNailY, int healthX, int healthY, int healthBarX, int healthBarY) {
	std::string pokemonName = player.getPokemon(pkmBagNumber).getName();
	int pokemonLevel = player.getPokemon(pkmBagNumber).getLevel();
	char pokemonSex = player.getPokemon(pkmBagNumber).getSex();
	int pokedexNumber = player.getPokemon(pkmBagNumber).getPokedexNumber();
	int pokemonCurrentHealtH = player.getPokemon(pkmBagNumber).getCurrentHealth();
	int pokemonMaxHealth = player.getPokemon(pkmBagNumber).getKP();

	//Draw Pokeball
	SDL_Rect srcRectBall = {0, 0, 20, 20};
	SDL_Rect dstRectBall = {ballX, ballY, 58, 58};
	graphics.blitSurface(this->_pokeBallTexture, &srcRectBall, &dstRectBall);

	Font::drawText(graphics, pokemonName, nameX, nameY, Font::getStandartFont(22), Font::colorWhite(), 200);

	// draw lv
	std::string level = "lv" + std::to_string(pokemonLevel) + "    sex: " + pokemonSex;
	Font::drawText(graphics, level, lvX, lvY, Font::getStandartFont(22), Font::colorWhite(), 200);

	//draw Health Text
	std::string health = std::to_string(pokemonCurrentHealtH) + "/ " + std::to_string(pokemonMaxHealth);
	Font::drawText(graphics, health, healthX, healthY, Font::getStandartFont(22), Font::colorWhite(), 200);

	//draw HealthBar
	int maxHealtWidth = 133;
	int healthW = maxHealtWidth * ((float)pokemonCurrentHealtH / pokemonMaxHealth);
	SDL_Rect srcRectHealthBar = {0, 0, 50, 5};
	SDL_Rect dstRectHealthBar = {healthBarX, healthBarY, healthW, 10};
	graphics.blitSurface(this->_healthBarTexture, &srcRectHealthBar, &dstRectHealthBar);

	// Draw pokemon Thumbnail
	int x = ((pokedexNumber - 1) % 25) * 32;
	int y = ((pokedexNumber - 1) / 25) * 33;
	SDL_Rect srcRectPokeTexture = {x, y, 32, 33};
	SDL_Rect dstRectPokeTexture = {thumbNailX, thumbNailY, 64, 66};
	graphics.blitSurface(this->_pokemonsTexture, &srcRectPokeTexture, &dstRectPokeTexture);
}

bool PokemonBag::visible() const {
	return this->_visible;
}

void PokemonBag::setVisible(bool value) {
	this->_visible = value;
}

