#include "engine/Stage.h"

#include <list>

namespace engine {

Stage::Stage() { this->init(); }

Stage::~Stage() {}

void Stage::loadRenderer(SDL_Renderer* renderer) { this->windowRenderer_ = renderer; }

void Stage::loadFont(TTF_Font* font) { this->font_ = font; }

std::int8_t Stage::run() {
    SDL_Event event;

    this->render();

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT: {
            return -1;
            break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            std::list<input::KeyAction> keyActions = keyboard.interpretAction();
            if (*keyActions.begin() == input::KeyAction::moveUp) {
                renderable.move(0, -1);
                keyActions.pop_front();
            } else if (*keyActions.begin() == input::KeyAction::moveDown) {
                renderable.move(0, 1);
                keyActions.pop_front();
            }
            if (*keyActions.begin() == input::KeyAction::moveLeft) {
                renderable.move(-1, 0);
                keyActions.pop_front();
            } else if (*keyActions.begin() == input::KeyAction::moveRight) {
                renderable.move(1, 0);
                keyActions.pop_front();
            }

            if (*keyActions.begin() == input::KeyAction::useInstinct) { keyActions.pop_front(); }
            break;
        }
        default: {
            break;
        }
        }
    }

    return 0;
}

void Stage::init() {
    if (this->windowRenderer_) {
        renderable.loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/bulonais.png",
                                this->windowRenderer_);
        renderable.move(400, 400);
    }
}

void Stage::render() { renderable.render(0, 0, this->windowRenderer_); }

} // namespace engine
