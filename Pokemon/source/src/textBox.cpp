#include "textBox.hpp"
#include "graphics.hpp"

#include <string>

#include "font.hpp"

TextBox::~TextBox() {
	SDL_DestroyTexture(this->_textBoxTexture);
	SDL_DestroyTexture(this->_fontTexture);
	delete this->_fontSurface;
}

TextBox::TextBox(Graphics &graphics) :
		textBoxPosX(57),
		textBoxPosY(370),
		textBoxWidth(260),
		textBoxHeight(52),

		// txtWidth and txtHeight are set through function queryTexture
		txtPosX(84),
		txtPosY(387),
		txtWidth(0),
		txtHeight(0),

		_visible(false),
		_sectionCounter(0),


		_fontTexture(NULL),
		_fontSurface(NULL)
{
	if (TTF_Init() < 0) {
		printf("\nError: Unable to initialize Font\n");
	}

	this->_sourceRect.x = 0;
	this->_sourceRect.y = 0;
	this->_sourceRect.w = 912;
	this->_sourceRect.h = 160;

	this->_textBoxDestinationRectangle.x = textBoxPosX;
	this->_textBoxDestinationRectangle.y = textBoxPosY;
	this->_textBoxDestinationRectangle.w = textBoxWidth * (int)globals::SPRITE_SCALE;
	this->_textBoxDestinationRectangle.h = textBoxHeight * (int)globals::SPRITE_SCALE;
	this->_textBoxTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/textBox.png"));
	if (this->_textBoxTexture == NULL) {
		printf("\nError: Unable to load image\n");
		printf(SDL_GetError());
	}
}

void TextBox::draw(Graphics &graphics) {
	 if (this->_visible) {
		// Draw TextBox
		graphics.blitSurface(this->_textBoxTexture, &this->_sourceRect, &this->_textBoxDestinationRectangle);

		// Draw Text
		this->_fontSurface = TTF_RenderUTF8_Blended_Wrapped(Font::getStandartFont(26), this->_textSections.at(this->_sectionCounter).c_str(), Font::colorBlack(),
				(this->textBoxWidth - 30) * (int)globals::SPRITE_SCALE);
		this->_fontTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), this->_fontSurface);
		SDL_QueryTexture(this->_fontTexture, NULL, NULL, &this->txtWidth, &this->txtHeight);
		SDL_Rect fontDestinationRectangle = { this->txtPosX, this->txtPosY,
				this->txtWidth/2 * (int)globals::SPRITE_SCALE,
				this->txtHeight/2 * (int)globals::SPRITE_SCALE};
		graphics.blitSurface(this->_fontTexture, &this->_sourceRect, &fontDestinationRectangle);
	 }
}

bool TextBox::isVisible() const {
	return this->_visible;
}

void TextBox::setVisible(bool value) {
	this->_visible = value;
}

// parse the string and fill textsection vector
void TextBox::setText(std::string strText) {
	// clear old text
	this->_textSections.clear();

	std::string delimiter = "###";

	size_t pos = 0;
	std::string section;
	while ((pos = strText.find(delimiter)) != std::string::npos) {
		section = strText.substr(0, pos);
	    this->_textSections.push_back(section);
	    strText.erase(0, pos + delimiter.length());
	}
	this->_textSections.push_back(strText);

	this->_visible = true;
}

void TextBox::nextTextSection() {
	if (this->_textSections.size() > this->_sectionCounter + 1) {
		this->_sectionCounter++;
	} else {
		this->setVisible(false);
		this->_sectionCounter = 0;
	}
}
