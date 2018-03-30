/*
 * player.hpp
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "animatedSprite.hpp"
#include "textBox.hpp"
#include "pokemon.hpp"

class Graphics;
class Slope;
class Level;
class Door;
class Npc;

class Player : public AnimatedSprite {
public:
	Player();
	~Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void setCamera(int levelWidth, int levelHeight);

	/* void moveLeft
	 *  Moves the player left by -dx
	 */
	void moveLeft();

	/* void moveRight
	 * moves the player right by dx
	 */
	void moveRight();

	/* void moveUp
	 * moves the player top by dy
	 */
	void moveUp();

	/* void moveDown
	 * moves the player down by -dy
	 */
	void moveDown();

	/* void stopMoving
	 * Stops moving the player
	 */
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector<Rectangle> &others);
	void handleSlopeCollisions(std::vector<Slope> &others);
	void handleDoorCollision(std::vector<Door> &others, Level &level, Graphics &graphics);
	void handleNpcCollision(std::vector<Npc*> others);

	const float getX() const;
	const float getY() const;
	const Direction getFacing() const;
	SDL_Rect getCamera();

	void addPokemon(Pokemon pokemon);
	Pokemon getPokemon(int index);
private:
	float _dx, _dy;

	Direction _facing;

	Pokemon _pokemons[6];
	int _amountPokemon;

	SDL_Rect _camera;
};



#endif /* PLAYER_HPP_ */
