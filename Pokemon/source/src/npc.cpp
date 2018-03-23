#include "npc.hpp"

//Base NPC class
Npc::Npc() {}

Npc::Npc(Graphics &graphics, std::string filePath, int sourceX, int sourceY, int width, int height,
		Vector2 spawnPoint, int timeToUpdate, std::string text) :
				AnimatedSprite(graphics, filePath, sourceX, sourceY, width, height,
						spawnPoint.x, spawnPoint.y, timeToUpdate),
						_facing(DOWN),
						_text(text)
{}

void Npc::update(int elapsedTime, Player &player) {
	AnimatedSprite::update(elapsedTime);
}

void Npc::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}

void Npc::setFacing(Direction facing) {
	this->_facing = facing;
	switch (facing) {
		case UP: this->playAnimation("idleUp");
			break;
		case DOWN: this->playAnimation("idleDown");
			break;
		case LEFT: this->playAnimation("idleLeft");
			break;
		case RIGHT: this->playAnimation("idleRight");
			break;
	}
}

std::string Npc::getText() {
	return this->_text;
}

//Dicker Class
Dicker::Dicker() {}

Dicker::Dicker(Graphics &graphics, Vector2 spawnPoint, std::string text) :
		Npc(graphics, "content/sprites/dicker.png", 0, 0, 16, 18, spawnPoint, 140, text)
{
	this->setupAnimations();
	this->playAnimation("idleDown");
}

void Dicker::update(int elapsedTime, Player &player) {
	this->_facing = player.getX() > this->_x ? RIGHT : LEFT;
	// this->playAnimation(this->_facing == RIGHT ? "idleRight" : "idleLeft");

	Npc::update(elapsedTime, player);
}

void Dicker::draw(Graphics &graphics) {
	Npc::draw(graphics);
}

void Dicker::setupAnimations() {
	this->addAnimation(1, 0, 0, "idleDown", 16, 18, Vector2(0,0));
	this->addAnimation(1, 0, 18, "idleUp", 16,18, Vector2(0,0));
	this->addAnimation(1, 0, 36, "idleRight", 12, 18, Vector2(0,0));
	this->addAnimation(1, 0, 55, "idleLeft", 12, 18, Vector2(0,0));
}

void Dicker::animationDone(std::string currentAnimation) {}

