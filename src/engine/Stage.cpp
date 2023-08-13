#include "engine/Stage.h"

#include <list>

#include "engine/Boss.h"
#include "engine/Bullet.h"
#include "engine/Text.h"
#include "utils/MovementPatterns.h"

namespace engine {

namespace {

//managers::RenderableManager& renderableManager = managers::RenderableManager::instance();

}

void Stage::renderText() {
    SDL_Color clr;
    clr.r = 255;
    clr.g = 255;
    clr.b = 255;
    clr.a = 255;
    std::shared_ptr<Text> lifeText = std::make_shared<Text>(850.f, 36.f);
    lifeText->loadFromText("Lifes: ", clr, this->windowRenderer_, this->font_);
    lifeText->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> scoreText1 = std::make_shared<Text>(850.f, 100.f);
    scoreText1->loadFromText("Power lvl: ", clr, this->windowRenderer_, this->font_);
    scoreText1->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> scoreText2 = std::make_shared<Text>(1150.f, 100.f, false);
    scoreText2->loadFromText(std::to_string(1 + this->player_->getPowerup() / 20) + " (" + (this->player_->getPowerup() >= 80 ? "MAX" : std::to_string(this->player_->getPowerup() % 20) + "/20") + ")", clr, this->windowRenderer_, this->font_);
    scoreText2->render(0, 0, this->windowRenderer_);
}

void Stage::renderHearts() {
    for (int it = 0; it < this->player_->getHp(); ++it) {
        std::shared_ptr<Renderable> heart = std::make_shared<Renderable>(950.f + 42 * it, 32.f);
        heart->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/life.png", this->windowRenderer_);
        heart->render(0, 0, this->windowRenderer_);
    }
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
    if (this->player_->getHp() < 1) { return -1; }

    this->render();

    return 0;
}

void Stage::init() {
    if (this->windowRenderer_) {
        managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
        
        std::shared_ptr<Renderable> background = std::make_shared<Renderable>(0.f, 0.f);
        background->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/background.png", this->windowRenderer_);
        renderableManager.addRenderable(background);


        player_ = std::make_shared<Player>(400.f, 400.f);
        player_->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/bulonais.png",
                                this->windowRenderer_);

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
    renderText();
    renderHearts();
}

} // namespace engine
