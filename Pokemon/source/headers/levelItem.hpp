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
	std::string getItemName() const;
	std::string getItemAction() const;
private:
	// name of the item
	std::string _name;
	// name of the items action eg. getHealthPotion
	std::string _action;
};



#endif /* LEVELITEM_HPP_ */
