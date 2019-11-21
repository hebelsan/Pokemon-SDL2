#include "Fight/fightTextBox.hpp"
#include "globals.hpp"
#include "font.hpp"

FightTextBox::FightTextBox(Graphics &graphics) :
	_visible(true)
{
	_textBoxSrcRect = {0,0,1280,210};

	_textBoxDstRect.x = 0;
	_textBoxDstRect.y = globals::SCREEN_HEIGHT - 120;
	_textBoxDstRect.w = globals::SCREEN_WIDTH;
	_textBoxDstRect.h = 120;

	_textBoxTexture  = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/fightScene/textBox.png"));
	if (this->_textBoxTexture == NULL) {
		printf("\nError: Unable to load image fighting map\n");
	}
}

void FightTextBox::draw(Graphics &graphics) {
	if (_visible) {
		graphics.blitSurface(_textBoxTexture, &_textBoxSrcRect, &_textBoxDstRect);
		Font::drawText(graphics, _text, 30, 380, Font::getStandartFont(28), Font::colorWhite(), 340);
	}
}

void FightTextBox::setVisible(bool visible) {
	this->_visible = visible;
}

void FightTextBox::setText(std::string text) {
	this->_text = text;
}

