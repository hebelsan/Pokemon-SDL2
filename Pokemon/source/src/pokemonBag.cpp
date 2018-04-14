#include "pokemonBag.hpp"
#include "graphics.hpp"
#include "player.hpp"
#include "globals.hpp"
#include "font.hpp"

#include <iostream>

PokemonBag::~PokemonBag() {
	SDL_DestroyTexture(this->_backgroundTexture);
	SDL_DestroyTexture(this->_pokeBallTexture);
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
		printf(SDL_GetError());
	}
	this->_pokeBallTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/PokemonBag/Pokeball_Passive.png"));
	if (this->_pokeBallTexture == NULL) {
		printf("\nError: Unable to load image pokeBall\n");
		printf(SDL_GetError());
	}
	this->_pokemonsTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/Pokemon/pokemonIcons.png"));
	if (this->_pokemonsTexture == NULL) {
		printf("\nError: Unable to load Pokemons Texture\n");
		printf(SDL_GetError());
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

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY, lvX, lvY, thumbNailX, thumbNailY);
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

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY, lvX, lvY, thumbNailX, thumbNailY);
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

		this->drawSinglePokemonStat(graphics, player, pkmBagNumber, ballX, ballY, nameX, nameY, lvX, lvY, thumbNailX, thumbNailY);
	}
	if (player.getNumberOfPokemons() > 3) {
		//Draw Pokeball
		SDL_Rect srcRectBall = {0, 0, 20, 20};
		SDL_Rect dstRectBall = {232, 177, 58, 58};
		graphics.blitSurface(this->_pokeBallTexture, &srcRectBall, &dstRectBall);

		std::string pokemonName = player.getPokemon(3).getName();
		int pokemonLevel = player.getPokemon(3).getLevel();
		char pokemonSex = player.getPokemon(3).getSex();

		SDL_Surface* fontSurfacePName = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
				pokemonName.c_str(), Font::colorWhite(), 200);
		int nameW, nameH;
		SDL_Texture* fontTexturePName = SDL_CreateTextureFromSurface(graphics.getRenderer(), fontSurfacePName);
		SDL_QueryTexture(fontTexturePName, NULL, NULL, &nameW, &nameH);
		SDL_Rect srcRectPName = {0,0, nameW, nameH};
		SDL_Rect dstRectPName = {325, 192, nameW, nameH};
		graphics.blitSurface(fontTexturePName, &srcRectPName, &dstRectPName);

		std::string level = "lv" + std::to_string(pokemonLevel) + "    sex: " + pokemonSex;
		SDL_Surface* levelSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
				level.c_str(), Font::colorWhite(), 200);
		int levelWidth, levelHeight;
		SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), levelSurface);
		SDL_QueryTexture(levelTexture, NULL, NULL, &levelWidth, &levelHeight);
		SDL_Rect srcRectLevel = {0,0, levelWidth, levelHeight};
		SDL_Rect dstRectLevel = {325,214, levelWidth, levelHeight};
		graphics.blitSurface(levelTexture, &srcRectLevel, &dstRectLevel);
	}
	if (player.getNumberOfPokemons() > 4) {
		//Draw Pokeball
		SDL_Rect srcRectBall = {0, 0, 20, 20};
		SDL_Rect dstRectBall = {232, 249, 58, 58};
		graphics.blitSurface(this->_pokeBallTexture, &srcRectBall, &dstRectBall);

		std::string pokemonName = player.getPokemon(4).getName();
		int pokemonLevel = player.getPokemon(4).getLevel();
		char pokemonSex = player.getPokemon(4).getSex();

		SDL_Surface* fontSurfacePName = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
				pokemonName.c_str(), Font::colorWhite(), 200);
		int nameW, nameH;
		SDL_Texture* fontTexturePName = SDL_CreateTextureFromSurface(graphics.getRenderer(), fontSurfacePName);
		SDL_QueryTexture(fontTexturePName, NULL, NULL, &nameW, &nameH);
		SDL_Rect srcRectPName = {0,0, nameW, nameH};
		SDL_Rect dstRectPName = {325, 264, nameW, nameH};
		graphics.blitSurface(fontTexturePName, &srcRectPName, &dstRectPName);

		std::string level = "lv" + std::to_string(pokemonLevel) + "    sex: " + pokemonSex;
		SDL_Surface* levelSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
				level.c_str(), Font::colorWhite(), 200);
		int levelWidth, levelHeight;
		SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), levelSurface);
		SDL_QueryTexture(levelTexture, NULL, NULL, &levelWidth, &levelHeight);
		SDL_Rect srcRectLevel = {0,0, levelWidth, levelHeight};
		SDL_Rect dstRectLevel = {325,286, levelWidth, levelHeight};
		graphics.blitSurface(levelTexture, &srcRectLevel, &dstRectLevel);
	}
	if (player.getNumberOfPokemons() > 5) {
		//Draw Pokeball
		SDL_Rect srcRectBall = {0, 0, 20, 20};
		SDL_Rect dstRectBall = {232, 321, 58, 58};
		graphics.blitSurface(this->_pokeBallTexture, &srcRectBall, &dstRectBall);

		std::string pokemonName = player.getPokemon(5).getName();
		int pokemonLevel = player.getPokemon(5).getLevel();
		char pokemonSex = player.getPokemon(5).getSex();

		SDL_Surface* fontSurfacePName = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
				pokemonName.c_str(), Font::colorWhite(), 200);
		int nameW, nameH;
		SDL_Texture* fontTexturePName = SDL_CreateTextureFromSurface(graphics.getRenderer(), fontSurfacePName);
		SDL_QueryTexture(fontTexturePName, NULL, NULL, &nameW, &nameH);
		SDL_Rect srcRectPName = {0,0, nameW, nameH};
		SDL_Rect dstRectPName = {325, 336, nameW, nameH};
		graphics.blitSurface(fontTexturePName, &srcRectPName, &dstRectPName);

		std::string level = "lv" + std::to_string(pokemonLevel) + "    sex: " + pokemonSex;
		SDL_Surface* levelSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
				level.c_str(), Font::colorWhite(), 200);
		int levelWidth, levelHeight;
		SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), levelSurface);
		SDL_QueryTexture(levelTexture, NULL, NULL, &levelWidth, &levelHeight);
		SDL_Rect srcRectLevel = {0,0, levelWidth, levelHeight};
		SDL_Rect dstRectLevel = {325,358, levelWidth, levelHeight};
		graphics.blitSurface(levelTexture, &srcRectLevel, &dstRectLevel);
	}
}

void PokemonBag::drawSinglePokemonStat(Graphics & graphics, Player &player, int pkmBagNumber, int ballX, int ballY,
			int nameX, int nameY, int lvX, int lvY, int thumbNailX, int thumbNailY) {
	std::string pokemonName = player.getPokemon(pkmBagNumber).getName();
	int pokemonLevel = player.getPokemon(pkmBagNumber).getLevel();
	char pokemonSex = player.getPokemon(pkmBagNumber).getSex();
	int pokedexNumber = player.getPokemon(pkmBagNumber).getPokedexNumber();

	//Draw Pokeball
	SDL_Rect srcRectBall = {0, 0, 20, 20};
	SDL_Rect dstRectBall = {ballX, ballY, 58, 58};
	graphics.blitSurface(this->_pokeBallTexture, &srcRectBall, &dstRectBall);

	SDL_Surface* fontSurfacePName = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
		pokemonName.c_str(), Font::colorWhite(), 200);
	int nameW, nameH;
	SDL_Texture* fontTexturePName = SDL_CreateTextureFromSurface(graphics.getRenderer(), fontSurfacePName);
	SDL_QueryTexture(fontTexturePName, NULL, NULL, &nameW, &nameH);
	SDL_Rect srcRectPName = {0,0, nameW, nameH};
	SDL_Rect dstRectPName = {nameX,nameY, nameW, nameH};
	graphics.blitSurface(fontTexturePName, &srcRectPName, &dstRectPName);

	std::string level = "lv" + std::to_string(pokemonLevel) + "    sex: " + pokemonSex;
	SDL_Surface* levelSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(22),
		level.c_str(), Font::colorWhite(), 200);
	int levelWidth, levelHeight;
	SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), levelSurface);
	SDL_QueryTexture(levelTexture, NULL, NULL, &levelWidth, &levelHeight);
	SDL_Rect srcRectLevel = {0,0, levelWidth, levelHeight};
	SDL_Rect dstRectLevel = {lvX, lvY, levelWidth, levelHeight};
	graphics.blitSurface(levelTexture, &srcRectLevel, &dstRectLevel);

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

