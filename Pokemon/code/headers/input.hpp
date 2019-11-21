/*
 * input.hpp
 * keeps track of keyboard state
 */

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <map>
#include <vector>
#include <SDL2/SDL.h>

class Input {
public:
	void beginNewFrame();
	void keyUpEvent(const SDL_Event &event);
	void keyDownEvent(const SDL_Event &event);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
	SDL_Scancode getPressedArrowKey();
private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;

	std::vector<SDL_Scancode> _heldArrowKeys;

	bool isArrowKey(SDL_Scancode key);
	void removeArrowKey(SDL_Scancode key);
};




#endif /* INPUT_HPP_ */
