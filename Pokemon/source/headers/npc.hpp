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
			int width, int heigth, Vector2 spawnPoint, int timeToUpdate);
	virtual void update(int elapsedTime, Player &player);
	virtual void draw(Graphics &graphics);
	void setFacing(Direction facing);
protected:
	Direction _facing;
};

class Dicker : public Npc {
public:
	Dicker();
	Dicker(Graphics &graphics, Vector2 spawnPoint);
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics);

	void animationDone(std::string currentAnimation);
	void setupAnimations();
};



#endif /* NPC_HPP_ */
