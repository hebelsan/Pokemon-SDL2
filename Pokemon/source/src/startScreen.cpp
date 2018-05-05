#include "startScreen.hpp"

#include "input.hpp"
#include "graphics.hpp"
#include "globals.hpp"
#include "music.hpp"

#include <iostream>

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 100 / FPS;
}

StartScreen::StartScreen(Graphics &graphics) :
		AnimatedSprite(graphics, "content/backgrounds/starter.png", 0, 0, 500, 450, 0, 0, 90)
{
	this->setupAnimations();
	this->playAnimation("start");
}

void StartScreen::setupAnimations() {
	this->addAnimation(7, 0, 0, "start", 500, 450, Vector2(0,0));
}

void StartScreen::animationDone(std::string currentAnimation) {}

void StartScreen::startStartScreenLoop(Graphics &graphics, Input &input, SDL_Event &event) {
	Music::getInstance()->loadMusicFile("content/music/TitleScreenTheme.mp3");
	Music::getInstance()->fadeIn(-1, 1000);

	int LAST_UPDATE_TIME = SDL_GetTicks();
		// start game loop
		while (true) {
			input.beginNewFrame();
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN) {
					if (event.key.repeat == 0) {
						input.keyDownEvent(event);
					}
				}
				else if (event.type == SDL_KEYUP) {
					input.keyUpEvent(event);
				}
				else if (event.type == SDL_QUIT) {
					return;
				}
			}
			if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
				return;
			}
			else if (input.wasKeyPressed(SDL_SCANCODE_SPACE) == true) {
				Music::getInstance()->fadeOut(2000);
				return;
			}
			else if (input.wasKeyPressed(SDL_SCANCODE_RETURN) == true) {
				Music::getInstance()->fadeOut(2000);
				return;
			}

			const int CURRENT_TIME_MS = SDL_GetTicks();
			int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
			this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
			LAST_UPDATE_TIME = CURRENT_TIME_MS;

			this->draw(graphics);
		}
}


void StartScreen::draw(Graphics &graphics) {
	graphics.clear();

	// draw this background
	AnimatedSprite::drawStartScreen(graphics);

	graphics.flip();
}

void StartScreen::update(float elapsedTime) {
	AnimatedSprite::update(elapsedTime);
}



