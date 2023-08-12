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

void enemyBulletStraightSlowMovement(float& x, float& y) {
    x = 0.f;
    y = 5.f;
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

            if (*keyActions.begin() == input::KeyAction::shootBullet && this->bulletFrameCounter_ > 4) {
                enableShooting = true;
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

    if (this->enemyBulletFrameCounter_ > 12) {
        for (int it = 0; it < 32; ++it) {
            Bullet* bullet = new Bullet(24 + 48 * (it % 16), 64 + 64 * (it / 16), true, enemyBulletStraightSlowMovement);
            bullet->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/wip.png", this->windowRenderer_);
            renderableManager.addRenderable(bullet);
            enemyBulletFrameCounter_ = 0;
        }
    }

    if (enableShooting) {
        Bullet* bullet1 = new Bullet(this->player_.X() + (this->player_.W() / 2) - 12, this->player_.Y(), false, playerBulletMovement);
        Bullet* bullet2 = new Bullet(this->player_.X() + (this->player_.W() / 2) + 12, this->player_.Y(), false, playerBulletMovement);
        Bullet* bullet3 = new Bullet(this->player_.X() + this->player_.W() / 2, this->player_.Y(), false, playerBulletMovement);
        bullet1->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
        bullet2->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
        bullet3->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
        renderableManager.addRenderable(bullet1);
        renderableManager.addRenderable(bullet2);
        renderableManager.addRenderable(bullet3);
        this->bulletFrameCounter_ = 0;
    }

    this->bulletFrameCounter_++;
    this->enemyBulletFrameCounter_++;

    this->player_.move(movX, movY);
    renderableManager.move();

    this->render();

    return 0;
}

void Stage::init() {
    if (this->windowRenderer_) {
        managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
        
        player_.loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/bulonais.png",
                                this->windowRenderer_);
        renderableManager.addRenderable(&player_);

        for (int it = 0; it < 32; ++it) {
            Renderable* bullet = new Renderable(24  + 48 * (it % 16), 32 + 64 * (it / 16));
            bullet->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/wip.png", this->windowRenderer_);
            renderableManager.addRenderable(bullet);
        }
    }
}

void Stage::render() { 
    managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
    renderableManager.render();
}

} // namespace engine
