#include "level.hpp"
#include "graphics.hpp"
#include "utils.hpp"
#include "npc.hpp"
#include "player.hpp"

#include "tinyxml2.h"

#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace tinyxml2;

Level::Level() {}

Level:: Level(std::string mapName, Graphics &graphics) :
		_mapName(mapName),
		_size(Vector2(0,0)),
		_backgroundTexture(NULL)
{
	this->loadMap(mapName, graphics);
}

Level::~Level() {

}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	// Parse the .tmx file
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/maps/" << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	//Get the width and the height of the whole map and sotre it in _size
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->_size = Vector2(width, height);

	//Get the width and the height of the tiles and store it in _tileSize
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_tileSize = Vector2(tileWidth, tileHeight);

	//loading the tileset
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss << "content";
			for (int i = 2; i < strlen(source); i++) {
				ss << source[i];
			}
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
			this->_tilesets.push_back(Tileset(tex, firstgid));

			// Get all the animation for that tileset
			XMLElement* pTileA = pTileset->FirstChildElement("tile");
			if (pTileA != NULL) {
				while (pTileA) {
					AnimatedTileInfo ati;
					ati.StartTileId = pTileA->IntAttribute("id") + firstgid;
					ati.TilesetsFirstGid = firstgid;
					XMLElement* pAnimation = pTileA->FirstChildElement("animation");
					if (pAnimation != NULL) {
						while (pAnimation) {
							XMLElement* pFrame = pAnimation->FirstChildElement("frame");
							if(pFrame != NULL){
								while(pFrame) {
									ati.TileIds.push_back(pFrame->IntAttribute("tileid") + firstgid);
									ati.Duration = pFrame->IntAttribute("duration");
									pFrame = pFrame->NextSiblingElement("frame");
								}
							}
							pAnimation = pAnimation->NextSiblingElement("animation");
						}
					}
					this->_animatedTileInfos.push_back(ati);
					pTileA = pTileA->NextSiblingElement("tile");
				}
			}
			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	// loading the layers
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			this->_mapW = pLayer->IntAttribute("width") * 32;
			this->_mapH = pLayer->IntAttribute("height") * 32;
			this->_backgroundTexture = SDL_CreateTexture(graphics.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->_mapW, this->_mapH);
			// Loading the data element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					// loading the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							// build each individual tile here
							// if gid is 0, no tile should be drawn, continue loop
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							// get the tileset for this spezific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							int closest = 0;
							for (int i = 0; i < this->_tilesets.size(); i++) {
								if (this->_tilesets[i].FirstGid <= gid) {
									if (this->_tilesets[i].FirstGid > closest) {
										closest = this->_tilesets[i].FirstGid;
										tls = this->_tilesets.at(i);
									}
								}
							}

							if (tls.FirstGid == -1) {
								// NO Tileset was found for this gid
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//Get the position of the tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							//Calculate the position of the tile in the tileset
							Vector2 finalTilesetposition = this->getTilesetPosition(tls, gid, tileWidth, tileHeight);

							// build the actual tile and add it to the level's tile list
							bool isAnimatedTile = false;
							AnimatedTileInfo ati;
							for (int i = 0; i < this->_animatedTileInfos.size(); i++) {
								if (this->_animatedTileInfos.at(i).StartTileId == gid) {
									ati = this->_animatedTileInfos.at(i);
									isAnimatedTile = true;
									break;
								}
							}
							if (isAnimatedTile == true) {
								std::vector<Vector2> tilesetPositions;
								for(int i = 0; i < ati.TileIds.size(); i++) {
									tilesetPositions.push_back(this->getTilesetPosition(tls, ati.TileIds.at(i),
											tileWidth, tileHeight));
								}
								AnimatedTile tile(tilesetPositions, ati.Duration,
										tls.Texture, Vector2(tileWidth, tileHeight), finalTilePosition);
								this->_animatedTileList.push_back(tile);
							}
							else {
								Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetposition,
										finalTilePosition);
								this->_tileList.push_back(tile);
							}
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
		}
	}

	// pares out the collisions
	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != NULL) {
		while (pObjectGroup) {
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream ss;
			ss << name;
			if (ss.str() == "collisions") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						this->_collisionRects.push_back(Rectangle(
								std::ceil(x) * globals::SPRITE_SCALE,
								std::ceil(y) * globals::SPRITE_SCALE,
								std::ceil(width) * globals::SPRITE_SCALE,
								std::ceil(height) * globals::SPRITE_SCALE
						));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			// other objectgroups go here with an els if (ss.str() == "watherver")
			else if (ss.str() == "slopes") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						std::vector<Vector2> points;
						Vector2 p1;
						p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));

						XMLElement* pPolyline = pObject->FirstChildElement("polyline");
						if (pPolyline != NULL) {
							std::vector<std::string> pairs;
							const char* pointString = pPolyline->Attribute("points");

							std::stringstream ss;
							ss << pointString;
							Utils::split(ss.str(), pairs, ' ');
							// Now we have each off the pairs, loop through the list of pairs and split them
							// into Vector2s and then store themin our points vector
							for (int i = 0; i < pairs.size(); i++) {
								std::vector<std::string> ps;
								Utils::split(pairs.at(i), ps, ',');
								points.push_back(Vector2(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
							}
						}

						for (int i = 0; i < points.size(); i += 2) {
							this->_slopes.push_back(Slope(
									Vector2((p1.x + points.at(i < 2 ? i : i - 1).x) * globals::SPRITE_SCALE,
											(p1.y + points.at(i < 2 ? i : i - 1).y) * globals::SPRITE_SCALE),
									Vector2((p1.x + points.at(i < 2 ? i + 1 : i).x) * globals::SPRITE_SCALE,
											(p1.y + points.at(i < 2 ? i + 1 : i).y) * globals::SPRITE_SCALE)
											));
						}

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			else if (ss.str() == "spawn points") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "player") {
							XMLElement* pProperties = pObject->FirstChildElement("properties");
							if (pProperties != NULL) {
								while (pProperties) {
									XMLElement* pProperty = pProperties->FirstChildElement("property");
									if (pProperty != NULL) {
										while (pProperty) {
											const char* name = pProperty->Attribute("name");
											std::stringstream ss;
											ss << name;
											if (ss.str() == "location") {
												const char* value = pProperty->Attribute("value");
												std::stringstream ss2;
												ss2 << value;
												std::string spawnPointName = ss2.str();
												// set new Spawn point with name = value
												this->_spawnPoints.insert(std::pair<std::string,Vector2>(spawnPointName, Vector2(std::ceil(x) * globals::SPRITE_SCALE, std::ceil(y) * globals::SPRITE_SCALE)));
											}
											pProperty = pProperty->NextSiblingElement("property");
										}
									}
									pProperties = pObject->NextSiblingElement("properties");
								}
							}
							pObject = pObject->NextSiblingElement("object");
						}
					}
				}
			}
			else if (ss.str() == "doors") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						float w = pObject->FloatAttribute("width");
						float h = pObject->FloatAttribute("height");
						Rectangle rect = Rectangle(x, y, w, h);

						XMLElement* pProperties = pObject->FirstChildElement("properties");
						if (pProperties != NULL) {
							while (pProperties) {
								XMLElement* pProperty = pProperties->FirstChildElement("property");
								std::string destinationSpawnPoint = "";
								std::string destinationMap = "";
								if (pProperty != NULL) {
									while (pProperty) {
										const char* name = pProperty->Attribute("name");
										std::stringstream ss;
										ss << name;
										if (ss.str() == "destination") {
											const char* value = pProperty->Attribute("value");
											std::stringstream ss2;
											ss2 << value;
											destinationMap = ss2.str();
										}
										if (ss.str() == "destinationSpawnPoint") {
											const char* value = pProperty->Attribute("value");
											std::stringstream ss2;
											ss2 << value;
											destinationSpawnPoint = ss2.str();
										}
										pProperty = pProperty->NextSiblingElement("property");
									}
									Door door = Door(rect, destinationMap, destinationSpawnPoint);
									this->_doorList.push_back(door);
								}
								pProperties = pObject->NextSiblingElement("properties");
							}
						}
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			else if (ss.str() == "NPC") {
				float x, y;
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						std::string npcText;
						XMLElement* pProperties = pObject->FirstChildElement("properties");
						if (pProperties != NULL) {
							while (pProperties) {
								XMLElement* pProperty = pProperties->FirstChildElement("property");
								if (pProperty != NULL) {
									while (pProperty) {
										const char* name = pProperty->Attribute("name");
										std::stringstream ss;
										ss << name;
										if (ss.str() == "text") {
											const char* value = pProperty->Attribute("value");
											std::stringstream ss2;
											ss2 << value;
											npcText = ss2.str();
										}
										pProperty = pProperty->NextSiblingElement("property");
									}
								}
								pProperties = pObject->NextSiblingElement("properties");
							}
						}
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						if (ss.str() == "dicker") {
							this->_npcs.push_back(new Dicker(graphics, Vector2(std::floor(x) * globals::SPRITE_SCALE,
									std::floor(y) * globals::SPRITE_SCALE), npcText));
						}
						if (ss.str() == "PokeProf") {
							this->_npcs.push_back(new PokeProf(graphics, Vector2(std::floor(x) * globals::SPRITE_SCALE,
																std::floor(y) * globals::SPRITE_SCALE), npcText));
						}
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			else if (ss.str() == "Item") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						float w = pObject->FloatAttribute("width");
						float h = pObject->FloatAttribute("height");
						Rectangle rect = Rectangle(x, y, w, h);
						std::string levelItemAction;

						XMLElement* pProperties = pObject->FirstChildElement("properties");
						if (pProperties != NULL) {
							while (pProperties) {
								XMLElement* pProperty = pProperties->FirstChildElement("property");
								if (pProperty != NULL) {
									while (pProperty) {
										const char* name = pProperty->Attribute("name");
										std::stringstream ss;
										ss << name;
										if (ss.str() == "action") {
											const char* value = pProperty->Attribute("value");
											std::stringstream ss2;
											ss2 << value;
											levelItemAction = ss2.str();
										}
										pProperty = pProperty->NextSiblingElement("property");
									}
								}
								pProperties = pObject->NextSiblingElement("properties");
							}
						}
						const char* name = pObject->Attribute("name");
						std::stringstream ss;
						ss << name;
						std::string levelItemName = ss.str();

						this->_levelItemList.push_back(LevelItem(rect, levelItemName, levelItemAction));

						pObject = pObject->NextSiblingElement("object");
					}
				}
			}

			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}

void Level::update(int elapsedTime, Player &player) {
	for(int i = 0; i < this->_animatedTileList.size(); i++) {
		this->_animatedTileList.at(i).update(elapsedTime);
	}
	for (int i = 0; i < this->_npcs.size(); i++) {
		this->_npcs.at(i)->update(elapsedTime, player);
	}
}

void Level::draw(Graphics &graphics, SDL_Rect camera) {
	SDL_SetRenderTarget(graphics.getRenderer(), this->_backgroundTexture);
	for (int i = 0; i < this->_tileList.size(); i++) {
		this->_tileList.at(i).draw(graphics);
	}
	for (int i = 0; i < this->_animatedTileList.size(); i++) {
		this->_animatedTileList.at(i).draw(graphics);
	}
	for (int i = 0; i < this->_npcs.size(); i++) {
		this->_npcs.at(i)->draw(graphics);
	}

	SDL_SetRenderTarget(graphics.getRenderer(), NULL);

	SDL_RenderClear(graphics.getRenderer());
	SDL_RenderCopy(graphics.getRenderer(), this->_backgroundTexture, &camera, NULL);
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other) {
	std::vector<Rectangle> others;
	for (int i = 0; i < this->_collisionRects.size(); i++) {
		if (this->_collisionRects.at(i).collidesWith(other)) {
			others.push_back(this->_collisionRects.at(i));
		}
	}
	return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other) {
	std::vector<Slope> others;
	for (int i = 0; i < this->_slopes.size(); i++) {
		if (this->_slopes.at(i).collideWith(other)) {
			others.push_back(this->_slopes.at(i));
		}
	}
	return others;
}

std::vector<Door> Level::checkDoorCollisions(const Rectangle &other) {
	std::vector<Door> others;
	for (int i = 0; i < this->_doorList.size(); i++) {
		if (this->_doorList.at(i).collidesWith(other)) {
			others.push_back(this->_doorList.at(i));
		}
	}
	return others;
}

std::vector<Npc*> Level::checkNpcCollisions(const Rectangle &other) {
	std::vector<Npc*> others;
		for (int i = 0; i < this->_npcs.size(); i++) {
			if (this->_npcs.at(i)->getBoundingBox().collidesWith(other)) {
				others.push_back(this->_npcs.at(i));
			}
		}
	return others;
}

const Vector2 Level::getPlayerSpawnPoint(std::string spawnPointLocation) const {
	return this->_spawnPoints.at(spawnPointLocation);
}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {
	int tilesetWidth, tilesetHeight;
	int tsxx, tsyy = 0;
	SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
	// to support multiple tilesets
	int tmGgid = gid + 1 - tls.FirstGid;

	tsxx = (tmGgid - 1) % (tilesetWidth / tileWidth);
	tsxx *= tileWidth;
	if (tsxx < 0) {
		tsxx = ((tilesetWidth / tileWidth) -1) * tileWidth;
		tsyy = 0;
		int amt = (gid / (tilesetWidth / tileWidth));
		amt -= 1;
		tsyy = tileHeight * amt;
	}
	else {
	tsyy = 0;
	int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
	tsyy = tileHeight * amt;
	}
	Vector2 finalTilesetposition = Vector2(tsxx, tsyy);
	return finalTilesetposition;
}

std::vector<Npc*> Level::getNpcs() const {
	return this->_npcs;
}

std::vector<LevelItem> Level::getLevelItems() const {
	return this->_levelItemList;
}
