#include "npc.hpp"
#include <iostream>

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

std::vector<Pokemon> Npc::getPokemons() {
	return this->_pokemons;
}

//Dicker Class
Dicker::Dicker() {}

Dicker::Dicker(Graphics &graphics, Vector2 spawnPoint, std::string text) :
		Npc(graphics, "content/sprites/NPC/dicker.png", 0, 0, 16, 18, spawnPoint, 140, text)
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

//Poke Professor Class
PokeProf::PokeProf() {}

PokeProf::PokeProf(Graphics &graphics, Vector2 spawnPoint, std::string text) :
		Npc(graphics, "content/sprites/NPC/PokemonProf.png", 0, 0, 17, 25, spawnPoint, 140, text)
{
	this->setupAnimations();
	this->playAnimation("idleDown");
}

void PokeProf::update(int elapsedTime, Player &player) {
	Npc::update(elapsedTime, player);
}

void PokeProf::draw(Graphics &graphics) {
	Npc::draw(graphics);
}

void PokeProf::setupAnimations() {
	this->addAnimation(1, 0, 0, "idleDown", 17, 25, Vector2(0,0));
	this->addAnimation(1, 0, 25, "idleUp", 17,25, Vector2(0,0));
	this->addAnimation(1, 0, 50, "idleRight", 17, 25, Vector2(0,0));
	this->addAnimation(1, 0, 75, "idleLeft", 17, 25, Vector2(0,0));
}

void PokeProf::animationDone(std::string currentAnimation) {}

//Base Trainer Class
Trainer::Trainer() {}

Trainer::Trainer(Graphics &graphics, Vector2 spawnPoint, std::string text, std::vector<Pokemon> pokemons) :
		Npc(graphics, "content/sprites/NPC/Trainer.png", 0, 0, 18, 23, spawnPoint, 140, text)
{
	this->setupAnimations();
	this->playAnimation("idleDown");
	this->_pokemons = pokemons;
}

void Trainer::update(int elapsedTime, Player &player) {
	Npc::update(elapsedTime, player);
}

void Trainer::draw(Graphics &graphics) {
	Npc::draw(graphics);
}

void Trainer::setupAnimations() {
	this->addAnimation(1, 0, 0, "idleDown", 18, 23, Vector2(0,0));
	this->addAnimation(1, 0, 23, "idleUp", 18,23, Vector2(0,0));
	this->addAnimation(1, 0, 46, "idleRight", 18, 23, Vector2(0,0));
	this->addAnimation(1, 0, 69, "idleLeft", 18, 23, Vector2(0,0));
}

void Trainer::animationDone(std::string currentAnimation) {}
