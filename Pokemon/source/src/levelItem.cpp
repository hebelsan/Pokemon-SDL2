#include "levelItem.hpp"

LevelItem::LevelItem() {}

LevelItem::LevelItem(Rectangle r, std::string itemName, std::string itemAction) :
		Rectangle(r.getLeft() * globals::SPRITE_SCALE, r.getTop() * globals::SPRITE_SCALE,
						r.getWidth() * globals::SPRITE_SCALE, r.getHeight() * globals::SPRITE_SCALE),
		_name(itemName),
		_action(itemAction)
{}

std::string LevelItem::getItemName() const {
	return this->_name;
}

std::string LevelItem::getItemAction() const {
	return this->_action;
}


