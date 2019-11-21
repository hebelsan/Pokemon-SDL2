#include "input.hpp"


// this function gets called at each new Frame
// to reset the keys that are no longer relevant
void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

// this gets called when a key has been pressed
void Input::keyDownEvent(const SDL_Event &event) {
	SDL_Scancode scnacode = event.key.keysym.scancode;
	this->_pressedKeys[scnacode] = true;
	this->_heldKeys[scnacode] = true;
	if (this->isArrowKey(scnacode)) {
		this->_heldArrowKeys.push_back(scnacode);
	}
}

// this gets called when a key has been released
void Input::keyUpEvent(const SDL_Event &event) {
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
	if (this->isArrowKey(event.key.keysym.scancode)) {
			this->removeArrowKey(event.key.keysym.scancode);
	}
}

// checks if a certain key was pressed
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}

// checks if a certain key was released
bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->_releasedKeys[key];
}

// checks if a certain key is currently held
bool Input::isKeyHeld(SDL_Scancode key) {
	return this->_heldKeys[key];
}

bool Input::isArrowKey(SDL_Scancode key) {
	return
			key == SDL_SCANCODE_UP ||
			key == SDL_SCANCODE_DOWN ||
			key == SDL_SCANCODE_LEFT ||
			key == SDL_SCANCODE_RIGHT;
}

void Input::removeArrowKey(SDL_Scancode key) {
	for (int i = 0; i < this->_heldArrowKeys.size(); i++) {
		if (this->_heldArrowKeys.at(i) == key) {
			this->_heldArrowKeys.erase(this->_heldArrowKeys.begin() + i);
		}
	}
}

SDL_Scancode Input::getPressedArrowKey() {
	if (!this->_heldArrowKeys.empty()) {
		return this->_heldArrowKeys.back();
	}
	else {
		return SDL_SCANCODE_UNKNOWN;
	}
}

