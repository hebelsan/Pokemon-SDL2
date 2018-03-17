/*
 * slope.hpp
 *
 *  Created on: 31.01.2018
 *      Author: Alexander
 */

#ifndef SLOPE_HPP_
#define SLOPE_HPP_

#include "globals.hpp"
#include "rectangle.hpp"

#include <cmath>

class Slope {
public:
	Slope() {}
	Slope(Vector2 p1, Vector2 p2) :
		_p1(p1),
		_p2(p2)
	{
		if (this->_p2.x - this->_p1.x != 0) {
			this->_slope = (fabs(this->_p2.y) - fabs(this->_p1.y)) / (fabs(this->_p2.x) - fabs(this->_p1.x));
		}
	}

	const inline float getSlope() const {
		return this->_slope;
	}

	const bool collideWith(const Rectangle &other) const {
		return
				(other.getRight() >= this->_p2.x &&
				other.getLeft() <= this->_p1.x &&
				other.getTop() <= this->_p2.y &&
				other.getBottom() >= this->_p1.y) ||
				(other.getRight() >= this->_p1.x &&
				other.getLeft() <= this->_p2.x &&
				other.getTop() <= this->_p1.y &&
				other.getBottom() >= this->_p2.y) ||
				(other.getLeft() <= this->_p1.x &&
				other.getRight() >= this->_p2.x &&
				other.getTop() <= this->_p1.y &&
				other.getBottom() >= this->_p2.y) ||
				(other.getLeft() <= this->_p2.x &&
				other.getRight() >= this->_p1.x &&
				other.getTop() <= this->_p2.y &&
				other.getBottom() >= this->_p1.y);
	}

	const inline Vector2 getP1() const { return this->_p1; }
	const inline Vector2 getP2() const { return this->_p2; }
private:
	Vector2 _p1, _p2;
	float _slope;
};



#endif /* SLOPE_HPP_ */
