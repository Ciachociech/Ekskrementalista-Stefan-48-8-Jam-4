#include "engine/Stage.h"

#include <list>

#include "engine/Bullet.h"

namespace engine {

namespace {

//managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

void playerBulletMovement(float& x, float& y) {
    x = 0.f;
    y = -6.f;
}

}

Stage::Stage() : player_(400.f, 400.f) { this->init(); }

Stage::~Stage() {}

void Stage::loadRenderer(SDL_Renderer* renderer) { this->windowRenderer_ = renderer; }

void Stage::loadFont(TTF_Font* font) { this->font_ = font; }

std::int8_t Stage::run() {
    SDL_Event event;

    float movX = 0;
    float movY = 0;

    managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

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

            if (*keyActions.begin() == input::KeyAction::shootBullet) {
                Bullet* bullet = new Bullet(this->player_.X() + this->player_.W() / 2, this->player_.Y(), false, playerBulletMovement);
                bullet->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
                renderableManager.addRenderable(bullet);
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

    this->player_.move(movX, movY);
    renderableManager.move();

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
