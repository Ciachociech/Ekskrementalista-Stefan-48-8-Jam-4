#include "engine/Stage.h"

#include <list>

#include "engine/Bullet.h"

namespace engine {

namespace {

//managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

void playerBulletMovement(float& x, float& y) {
    x = 0.f;
    y = -9.f;
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
    bool enableShooting = false;

    managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

    {
        std::list<input::KeyAction> keyActions = keyboard.interpretMultipleAction();

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

        if (*keyActions.begin() == input::KeyAction::shootBullet && this->bulletFrameCounter_ > 4) {
            enableShooting = true;
            keyActions.pop_front();
        }
    }

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT: {
            return -1;
            break;
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            std::list<input::KeyAction> keyActions = keyboard.interpretSingleAction();

            if (*keyActions.begin() == input::KeyAction::useInstinct) { keyActions.pop_front(); }
            break;
        }
        default: {
            break;
        }
        }
    }

    if (enableShooting) {
        Bullet* bullet = new Bullet(this->player_.X() + this->player_.W() / 2, this->player_.Y(), false, playerBulletMovement);
        bullet->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
        renderableManager.addRenderable(bullet);
        this->player_.resetBulletFrameCounter();
    }

    this->player_.update(movX, movY);
    renderableManager.update();

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
