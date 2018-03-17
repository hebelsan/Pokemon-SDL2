#include "animatedSprite.hpp"
#include "graphics.hpp"
#include "sprite.hpp"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
			float posX, float posY, float timeToUpdate) :
					Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
					_frameIndex(0),
					_timeToUpdate(timeToUpdate),
					_visible(true),
					_currentAnimationOnce(false),
					_currentAnimation(""),
					_timeElapsed(0.0)
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		SDL_Rect newRect = { (i + x) * width, y, width, height };
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	this->_offset.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations() {
	this->_animations.clear();
	this->_offset.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible) {
	this->_visible = visible;
}

void AnimatedSprite::stopAnimation() {
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime) {
	Sprite::update();

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate) {
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
		}
		else {
			if (this->_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->stopAnimation();
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {

	if (this->_visible) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offset[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offset[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
		destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}

void AnimatedSprite::drawPlayer(Graphics &graphics, int x, int y, SDL_Rect cameraRect) {
	if (this->_visible) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offset[this->_currentAnimation].x - cameraRect.x;
		destinationRectangle.y = y + this->_offset[this->_currentAnimation].y - cameraRect.y;
		destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
		destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}

void AnimatedSprite::drawStartScreen(Graphics &graphics) {
	if (this->_visible) {
		SDL_Rect destinationRectangle;
		destinationRectangle.x = 0 + this->_offset[this->_currentAnimation].x;
		destinationRectangle.y = 0 + this->_offset[this->_currentAnimation].y;
		destinationRectangle.w = globals::SCREEN_WIDTH/2 * globals::SPRITE_SCALE;
		destinationRectangle.h = globals::SCREEN_HEIGHT/2 * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}
