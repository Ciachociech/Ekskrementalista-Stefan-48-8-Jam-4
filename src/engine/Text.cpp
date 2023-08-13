#include "engine/Text.h"

namespace engine {
	
Text::Text() : txt_(), isLeftside_(true), alignX_(0) {}

Text::Text(int x, int y, bool isLeftSide) : Renderable(x, y), txt_(), isLeftside_(isLeftSide), alignX_(x) {}

bool Text::loadFromText(std::string txt, SDL_Color txtColor, SDL_Renderer* renderer, TTF_Font* font) {	
	this->txt_ = txt;
	return Renderable::loadFromText(this->alignX_, txt, txtColor, renderer, font, this->isLeftside_);
}

std::string& Text::getText() { return this->txt_; }

}