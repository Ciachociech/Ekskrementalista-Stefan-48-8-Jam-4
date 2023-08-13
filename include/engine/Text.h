#ifndef ENGINE_TEXT_H_
#define ENGINE_TEXT_H_

#include <SDL_ttf.h>

#include "Renderable.h"

namespace engine {

class Text : public Renderable {
private:
	std::string txt_;
	bool isLeftside_;
	int alignX_;
public:
	Text();
	Text(int x, int y, bool isLeftSide = true);

	bool loadFromText(std::string txt, SDL_Color txtColor, SDL_Renderer* renderer, TTF_Font* font);
	std::string& getText();
};

}

#endif // !ENGINE_TEXT_H_
