#include "engine/Stage.h"

#include <list>

#include "engine/Boss.h"
#include "engine/Bullet.h"
#include "utils/MovementPatterns.h"

namespace engine {

namespace {

//managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

}

Stage::Stage() { this->init(); }

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

        if (*keyActions.begin() == input::KeyAction::shootBullet && this->player_->getUpdateFrameCounter() > (this->player_->getPowerup() < 20 ? 12 : this->player_->getPowerup() < 60 ? 6 : 4)) {
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
        if (this->player_->getPowerup() < 40 || this->player_->getPowerup() >= 80) {
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this->player_->X() - 4 + this->player_->W() / 2, this->player_->Y(), playerBulletCenterMovement);
            bullet->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
            bullet->setHitboxRadius(bullet->W() / 2);
            renderableManager.addCollisionable(bullet);
        }
        if (this->player_->getPowerup() >= 40) {
            std::shared_ptr<Bullet> bullet1 = std::make_shared<Bullet>(this->player_->X() - 16 + this->player_->W() / 2, this->player_->Y(), this->player_->getPowerup() < 80 ? playerBulletCenterMovement : playerBulletLeftMovement);
            std::shared_ptr<Bullet> bullet2 = std::make_shared<Bullet>(this->player_->X() + 8 + this->player_->W() / 2, this->player_->Y(), this->player_->getPowerup() < 80 ? playerBulletCenterMovement : playerBulletRightMovement);
            bullet1->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
            bullet2->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
            bullet1->setHitboxRadius(bullet1->W() / 2);
            bullet2->setHitboxRadius(bullet2->W() / 2);
            renderableManager.addCollisionable(bullet1);
            renderableManager.addCollisionable(bullet2);
        }
        this->player_->resetUpdateFrameCounter();
    }

    this->player_->update(movX, movY);
    renderableManager.update();

    this->render();

    return 0;
}

void Stage::init() {
    if (this->windowRenderer_) {
        player_ = std::make_shared<Player>(400.f, 400.f);
        player_->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/bulonais.png",
                                this->windowRenderer_);

        managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
        renderableManager.addCollisionable(player_);

        std::shared_ptr<Boss> boss = std::make_shared<Boss>(400.f - 24.f, 50.f, bossKretkaMovement);
        boss->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/skrobella.png", this->windowRenderer_);
        boss->setHitboxRadius(boss->W() / 2);
        renderableManager.addCollisionable(boss);
    }
}

void Stage::render() { 
    managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
    renderableManager.render();
}

} // namespace engine
