/*
 * startScreen.hpp
 *
 *  Created on: 31.01.2018
 *      Author: Alexander
 */

#ifndef STARTSCREEN_HPP_
#define STARTSCREEN_HPP_

#include <SDL2/SDL.h>
#include "animatedSprite.hpp"

class Graphics;
class Input;
class Music;


class StartScreen : public AnimatedSprite {
public:
	StartScreen(Graphics &graphics);
	// show startScreen until enter is pressed
	void startStartScreenLoop(Graphics &graphics, Input &input, SDL_Event &event, Music &music);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();
};



#endif /* STARTSCREEN_HPP_ */
