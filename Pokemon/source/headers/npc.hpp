/*
 * npc.hpp
 *
 */

#ifndef NPC_HPP_
#define NPC_HPP_

#include "animatedSprite.hpp"
#include "globals.hpp"
#include "player.hpp"

#include <string>

class Npc : public AnimatedSprite {
public:
	Npc();
	Npc(Graphics &graphics, std::string filePath, int sourceX, int sourceY,
			int width, int heigth, Vector2 spawnPoint, int timeToUpdate, std::string text);
	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphics &graphics);
	void setFacing(Direction facing);
	std::string getText();
	std::vector<Pokemon> getPokemons();
protected:
	Direction _facing;
	std::string _text;
	std::vector<Pokemon> _pokemons;
};

class Dicker : public Npc {
public:
	Dicker();
	Dicker(Graphics &graphics, Vector2 spawnPoint, std::string text);
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);

	void animationDone(std::string currentAnimation);
	void setupAnimations();
};

class PokeProf : public Npc {
public:
	PokeProf();
	PokeProf(Graphics &graphics, Vector2 spawnPoint, std::string text);
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);

	void animationDone(std::string currentAnimation);
	void setupAnimations();
};

class Trainer : public Npc {
public:
	Trainer();
	Trainer(Graphics &graphics, Vector2 spawnPoint, std::string text, std::vector<Pokemon>);
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);

	void animationDone(std::string currentAnimation);
	void setupAnimations();
};



#endif /* NPC_HPP_ */
