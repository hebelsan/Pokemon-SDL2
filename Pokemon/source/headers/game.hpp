/*
 * game.hpp
 *
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "player.hpp"
#include "level.hpp"
#include "graphics.hpp"


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
};



#endif /* GAME_HPP_ */
