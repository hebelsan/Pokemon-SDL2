/*
 * levelItem.hpp
 *
 *  Created on: 28.03.2018
 *      Author: Alexander
 */

#ifndef LEVELITEM_HPP_
#define LEVELITEM_HPP_

#include "rectangle.hpp"
#include <string>

class LevelItem : public Rectangle {
public:
	LevelItem();
	LevelItem(Rectangle r, std::string itemName, std::string itemAction);
private:
	std::string _name;
	std::string _action;
};



#endif /* LEVELITEM_HPP_ */
