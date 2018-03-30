#include "player.hpp"
#include "graphics.hpp"
#include "slope.hpp"
#include "level.hpp"
#include "door.hpp"
#include "npc.hpp"

#include <iostream>


namespace player_constants {
	const float WALK_SPEED = 0.1f;
}

Player::Player() {}

Player::~Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "content/sprites/Ash.png", 0, 0, 16, 19, spawnPoint.x, spawnPoint.y, 150),
	_dx(0),
	_dy(0),
	_facing(DOWN),
	_camera({0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT}),
	_amountPokemon(0)
{
	graphics.loadImage("content/sprites/Ash.png");
	this->setupAnimations();
	this->playAnimation("IdleDown");
}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, "IdleDown", 16, 19, Vector2(0,0));
	this->addAnimation(1, 0, 19, "IdleLeft", 16, 19, Vector2(0,0));
	this->addAnimation(1, 1, 38, "IdleRight", 16, 19, Vector2(0,0));
	this->addAnimation(1, 0, 57, "IdleUp", 16, 19, Vector2(0,0));
	this->addAnimation(4, 0, 0, "RunDown", 16, 19, Vector2(0,0));
	this->addAnimation(4, 0, 19, "RunLeft", 16, 19, Vector2(0,0));
	this->addAnimation(4, 0, 38, "RunRight", 16, 19, Vector2(0,0));
	this->addAnimation(4, 0, 57, "RunUp", 16, 19, Vector2(0,0));
}

void Player::animationDone(std::string currentAnimation) {}

const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const {
	return this->_y;
}

const Direction Player::getFacing() const {
	return this->_facing;
}

SDL_Rect Player::getCamera() {
	return this->_camera;
}

void Player::moveLeft() {
	this->_dx = -player_constants::WALK_SPEED;
	this->_dy = 0;
	this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->_dx = player_constants::WALK_SPEED;
	this->_dy = 0;
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::moveUp() {
	this->_dy = -player_constants::WALK_SPEED;
	this->_dx = 0;
	this->playAnimation("RunUp");
	this->_facing = UP;
}

void Player::moveDown() {
	this->_dy = player_constants::WALK_SPEED;
	this->_dx = 0;
	this->playAnimation("RunDown");
	this->_facing = DOWN;
}

void Player::stopMoving() {
	this->_dx = 0.0f;
	this->_dy = 0.0f;
	switch(this->_facing) {
	case RIGHT: playAnimation("IdleRight");
		break;
	case LEFT: playAnimation("IdleLeft");
		break;
	case UP: playAnimation("IdleUp");
		break;
	case DOWN: playAnimation("IdleDown");
	}
}

void Player::setCamera(int levelWidth, int levelHeight) {
    //Center the camera over the dot
    this->_camera.x = ( this->_x + 16 / 2 ) - globals::SCREEN_WIDTH / 2;
    this->_camera.y = ( this->_y + 19 / 2 ) - globals::SCREEN_HEIGHT / 2;

    //Keep the camera in bounds.
    if( this->_camera.x < 0 )
    {
        this->_camera.x = 0;
    }
    if( this->_camera.y < 0 )
    {
        this->_camera.y = 0;
    }
    if( this->_camera.x > levelWidth - this->_camera.w )
    {
    	this->_camera.x = levelWidth - this->_camera.w;
    }
    if( this->_camera.y > levelHeight - this->_camera.h )
    {
    	this->_camera.y = levelHeight - this->_camera.h;
    }
}

//void handleTileCollisions
// handles collisions with all tiles the player is colliding with
void Player::handleTileCollisions(std::vector<Rectangle> &others) {
	// Figur out what side the collision happend on and move the player accordingly
	for (int i = 0; i < others.size(); i++) {
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->_y = others.at(i).getBottom() + 1;
				this->_dy = 0;
				break;
			case sides::BOTTOM:
				this->_y = others.at(i).getTop() - this->_boundingBox.getHeight() - 1;
				this->_dy = 0;
				break;
			case sides::LEFT:
				this->_x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = others.at(i).getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			}
		}
	}
}

void Player::handleSlopeCollisions(std::vector<Slope> &others) {
	for (int i = 0; i < others.size(); i++) {
		// calculate where on the slope the player is touching
		// and use y=mx+b to figure out the y position to place  him at
		// first calculate "b"
		int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));

		// now get players center x
		int centerX = this->_boundingBox.getCenterX();

		// now pass that x into the equation y = mx + b (using our newly found b and x)) to get the new y position
		int newY = (others.at(i).getSlope() * centerX) + b - 8; // 8 is temporary to fix a problem

		// Re-position the player to the correct "y"
		this->_y = newY - this->_boundingBox.getHeight();
	}
}

void Player::handleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics) {
	for (int i = 0; i < others.size(); i++) {
		level = Level(others.at(i).getDestination(), graphics);
		this->_x = level.getPlayerSpawnPoint(others.at(i).getDestinationSpawnPoint()).x;
		this->_y = level.getPlayerSpawnPoint(others.at(i).getDestinationSpawnPoint()).y;
	}
}

void Player::handleNpcCollision(std::vector<Npc*> others) {
	// Figur out what side the collision happend on and move the player accordingly
	for (int i = 0; i < others.size(); i++) {
		Rectangle npcRec = others.at(i)->getBoundingBox();
		sides::Side collisionSide = Sprite::getCollisionSide(npcRec);
		if (collisionSide != sides::NONE) {
			switch (collisionSide) {
			case sides::TOP:
				this->_y = others.at(i)->getBoundingBox().getBottom() + 1;
				this->_dy = 0;
				break;
			case sides::BOTTOM:
				this->_y = others.at(i)->getBoundingBox().getTop() - this->_boundingBox.getHeight() - 1;
				this->_dy = 0;
				break;
			case sides::LEFT:
				this->_x = others.at(i)->getBoundingBox().getRight() + 1;
				break;
			case sides::RIGHT:
				this->_x = others.at(i)->getBoundingBox().getLeft() - this->_boundingBox.getWidth() - 1;
				break;
			}
		}
	}
}

void Player::update(float elapsedTime) {
	// Move by dx
	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::drawPlayer(graphics, this->_x, this->_y, this->_camera);
}

void Player::addPokemon(Pokemon pokemon) {
	if (this->_amountPokemon < 6) {
		this->_pokemons[_amountPokemon] = pokemon;
		_amountPokemon++;
	}
}

Pokemon Player::getPokemon(int index) {
	if (index > this->_amountPokemon) {
		std::cout << "FALSCHER INDEX ZUGRIFF AUF PLAYERS POKEMON" << std::endl;
	}
	return this->_pokemons[index];
}



