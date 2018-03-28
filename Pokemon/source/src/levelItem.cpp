#include "levelItem.hpp"

LevelItem::LevelItem() {}

LevelItem::LevelItem(Rectangle r, std::string itemName, std::string itemAction) :
		Rectangle(r.getLeft() * globals::SPRITE_SCALE, r.getTop() * globals::SPRITE_SCALE,
						r.getWidth() * globals::SPRITE_SCALE, r.getHeight() * globals::SPRITE_SCALE),
		_name(itemName),
		_action(itemAction)
{}




