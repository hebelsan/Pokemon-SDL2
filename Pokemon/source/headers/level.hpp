/*
 * level.hpp
 *
 *  Created on: 29.01.2018
 *      Author: Alexander
 */

#ifndef LEVEL_HPP_
#define LEVEL_HPP_


#include <door.hpp>
#include "globals.hpp"
#include "tile.hpp"
#include "rectangle.hpp"
#include "slope.hpp"
#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "animatedTile.hpp"
#include "levelItem.hpp"

class Graphics;
class Npc;
class Player;
struct Tileset;

class Level {
public:
	Level();
	Level(std::string mapName, Graphics &graphics);
	~Level();
	void update(int elapsedTime, Player &player);
	void draw(Graphics &graphics, SDL_Rect other);

	std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
	std::vector<Slope> checkSlopeCollisions(const Rectangle &other);
	std::vector<Door> checkDoorCollisions(const Rectangle &other);
	std::vector<Npc*> checkNpcCollisions(const Rectangle &other);

	const Vector2 getPlayerSpawnPoint(std::string spawnPointLocation) const;

	std::vector<Npc*> getNpcs() const;
	std::vector<LevelItem> getLevelItems() const;

	const int getMapWidth() const {
		return _mapW;
	}
	const int getMapHeight() const {
		return _mapH;
	}
private:
	std::string _mapName;
	std::map<std::string, Vector2> _spawnPoints;

	int _mapW, _mapH;

	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<Rectangle> _collisionRects;
	std::vector<Slope> _slopes;

	std::vector<AnimatedTile> _animatedTileList;
	std::vector<AnimatedTileInfo> _animatedTileInfos;

	std::vector<Door> _doorList;

	std::vector<Npc*> _npcs;

	std::vector<LevelItem> _levelItemList;

	/* void loadMap
	 * loads a map
	 */
	void loadMap(std::string mapName, Graphics &graphics);

	Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);
};

// Tileset structure
struct Tileset {
	SDL_Texture* Texture;
	int FirstGid;
	Tileset() {
		this->FirstGid = -1;
	}
	Tileset(SDL_Texture* texture, int FirstGid) {
		this->Texture = texture;
		this->FirstGid = FirstGid;
	}
};



#endif /* LEVEL_HPP_ */
