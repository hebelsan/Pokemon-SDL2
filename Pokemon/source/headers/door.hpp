/*
 * Door.hpp
 *
 */

#ifndef DOOR_HPP_
#define DOOR_HPP_

#include "rectangle.hpp"
#include "globals.hpp"
#include <string>

class Door : public Rectangle {
public:
	Door();
	Door(Rectangle r, std::string destinationMap, std::string destinationSpawnPoint) :
		Rectangle(r.getLeft() * globals::SPRITE_SCALE, r.getTop() * globals::SPRITE_SCALE,
				r.getWidth() * globals::SPRITE_SCALE, r.getHeight() * globals::SPRITE_SCALE),
	_destination(destinationMap),
	_destinationSpawnPoint(destinationSpawnPoint)
	{}

	const inline Rectangle getRectangle() const { return this->getRect(); }
	const inline std::string getDestination() const { return this->_destination; }
	const inline std::string getDestinationSpawnPoint() const { return this->_destinationSpawnPoint; }

private:
	std::string _destination;
	std::string _destinationSpawnPoint;
};



#endif /* DOOR_HPP_ */
