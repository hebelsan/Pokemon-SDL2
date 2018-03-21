/*
 * game.hpp
 *
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "player.hpp"
#include "level.hpp"
#include "graphics.hpp"
#include "GUI.hpp"


class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Player _player;

	Level _level;

	Graphics _graphics;

	GUI _gui;
};



#endif /* GAME_HPP_ */
