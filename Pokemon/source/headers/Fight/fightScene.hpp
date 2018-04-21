/*
 * FightScene.hpp
 *
 *  Created on: 21.04.2018
 *      Author: Alexander
 */

#ifndef FIGHTSCENE_HPP_
#define FIGHTSCENE_HPP_

#include "graphics.hpp"
#include "player.hpp"

class FightScene {
public:
	~FightScene();
	FightScene();
	FightScene(Graphics &graphics);
	void draw(Graphics &graphics, Player &player);

	bool visible() const;
	void setVisible(bool value);
private:
	bool _visible;

	SDL_Rect _backgroundSrcRect;
	SDL_Rect _backgroundDstRect;
	SDL_Texture* _backgroundTexture;
};



#endif /* FIGHTSCENE_HPP_ */
