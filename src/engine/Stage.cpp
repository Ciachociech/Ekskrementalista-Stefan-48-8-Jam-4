#include "engine/Stage.h"

#include <list>

namespace engine {

namespace {

//managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

}

Stage::Stage() : player_(400.f, 400.f) { this->init(); }

Stage::~Stage() {}

void Stage::loadRenderer(SDL_Renderer* renderer) { this->windowRenderer_ = renderer; }

void Stage::loadFont(TTF_Font* font) { this->font_ = font; }

std::int8_t Stage::run() {
    SDL_Event event;

    float movX = 0;
    float movY = 0;

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
                movY -= playerMovement;
                keyActions.pop_front();
            } else if (*keyActions.begin() == input::KeyAction::moveDown) {
                movY += playerMovement;
                keyActions.pop_front();
            }
            if (*keyActions.begin() == input::KeyAction::moveLeft) {
                movX -= playerMovement;
                keyActions.pop_front();
            } else if (*keyActions.begin() == input::KeyAction::moveRight) {
                movX += playerMovement;
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

    player_.move(movX, movY);

    this->render();

    return 0;
}

void Stage::init() {
    if (this->windowRenderer_) {
        player_.loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/bulonais.png",
                                this->windowRenderer_);

        managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
        renderableManager.addRenderable(&player_);
    }
}

void Stage::render() { 
    managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
    renderableManager.render(); 
}

} // namespace engine
