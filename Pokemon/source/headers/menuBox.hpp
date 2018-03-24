/*
 * menuBox.hpp
 *
 *  Created on: 24.03.2018
 *      Author: Alexander
 */

#ifndef MENUBOX_HPP_
#define MENUBOX_HPP_

#include <SDL2/SDL.h>
class Graphics;

class MenuBox {
public:
	~MenuBox();
	MenuBox();
	MenuBox(Graphics &graphics);
	void draw(Graphics &graphics);

	bool visible() const;
	void setVisible(bool value);
private:
	bool _visible;

	const int _menuBoxWidth = 90;
	const int _menuBoxHeight = 170;
	SDL_Rect _menuBoxSourceRect;
	SDL_Rect _menuBoxDestinationRect;
	SDL_Texture* _menuBoxTexture;

	SDL_Rect _menuSelectorSourceRect;
	SDL_Rect _menuSelectorDestinationRect;
	SDL_Texture* _menuSelectorTexture;
};




#endif /* MENUBOX_HPP_ */
