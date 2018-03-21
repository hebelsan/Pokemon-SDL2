#include "textBox.hpp"
#include "graphics.hpp"

TextBox::~TextBox() {
	TTF_CloseFont(this->_font);
	SDL_DestroyTexture(this->_spriteSheet);
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
	_font = TTF_OpenFont("content/fonts/Pokemon_font.ttf", 26);
	this->_fontColor.r = 0;
	this->_fontColor.g = 0;
	this->_fontColor.b = 0;

	this->_textSections.push_back("hallo!");
	this->_textSections.push_back("Blütenburg gefällt mir sehr gut.");

	this->_sourceRect.w = 912;
	this->_sourceRect.h = 160;
	this->_sourceRect.x = 0;
	this->_sourceRect.y = 0;
	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/sprites/textBox.png"));
	if (this->_spriteSheet == NULL) {
		printf("\nError: Unable to load image\n");
		printf(SDL_GetError());
	}
}

void TextBox::draw(Graphics &graphics) {
	 if (this->_visible) {
		// Draw TextBox
		SDL_Rect destinationRectangle = { textBoxPosX, textBoxPosY,
				textBoxWidth * (int)globals::SPRITE_SCALE,
				textBoxHeight * (int)globals::SPRITE_SCALE};
		graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);

		// Draw Text
		this->_fontSurface = TTF_RenderText_Blended_Wrapped(this->_font, this->_textSections.at(this->_sectionCounter).c_str(), this->_fontColor,
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

void TextBox::nextTextSection() {
	if (this->_textSections.size() > this->_sectionCounter + 1) {
		this->_sectionCounter++;
	} else {
		this->setVisible(false);
		this->_sectionCounter = 0;
	}
}
