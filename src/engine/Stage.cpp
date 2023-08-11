#include "engine/Stage.h"

namespace engine {

Stage::Stage() { this->init(); }

Stage::~Stage() {}

void Stage::loadRenderer(SDL_Renderer* renderer) { this->windowRenderer_ = renderer; }

void Stage::loadFont(TTF_Font* font) { this->font_ = font; }

int Stage::run() {
    SDL_Event event;

    this->render();

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        default: {
            return 0;
        }
        }
    }

    return 0;
}

void Stage::init() {
    renderable.loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/bulonais.png",
                            this->windowRenderer_);
    renderable.setXY(400, 400);
}

void Stage::render() { renderable.render(0, 0, this->windowRenderer_); }

} // namespace engine
