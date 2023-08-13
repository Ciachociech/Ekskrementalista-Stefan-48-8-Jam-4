#include "engine/Stage.h"

#include <list>

#include "engine/Boss.h"
#include "engine/Bullet.h"
#include "engine/Text.h"
#include "managers/ScoreManager.h"
#include "utils/MovementPatterns.h"

namespace engine {

namespace {

//managers::RenderableManager& renderableManager = managers::RenderableManager::instance();
managers::ScoreManager& scoreManager = managers::ScoreManager::instance();

}

void Stage::renderText() {
    SDL_Color clr;
    clr.r = 255;
    clr.g = 255;
    clr.b = 255;
    clr.a = 255;
    std::shared_ptr<Text> lifeText = std::make_shared<Text>(850.f, 36.f);
    lifeText->loadFromText(*this->lang_ == Language::ENGLISH ? "Lifes: " : u8"¯ycia: ", clr, this->windowRenderer_, this->font_);
    lifeText->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> powerText1 = std::make_shared<Text>(850.f, 100.f);
    powerText1->loadFromText(*this->lang_ == Language::ENGLISH ? "Power level: " : u8"Poziom mocy: ", clr, this->windowRenderer_, this->font_);
    powerText1->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> powerText2 = std::make_shared<Text>(1150.f, 100.f, false);
    powerText2->loadFromText(std::to_string(1 + this->player_->getPowerup() / 10) + " (" + (this->player_->getPowerup() >= 40 ? "MAX" : std::to_string(this->player_->getPowerup() % 10) + "/10") + ")", clr, this->windowRenderer_, this->font_);
    powerText2->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> scoreText1 = std::make_shared<Text>(850.f, 164.f);
    scoreText1->loadFromText(*this->lang_ == Language::ENGLISH ? "Score: " : u8"Wynik: ", clr, this->windowRenderer_, this->font_);
    scoreText1->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> scoreText2 = std::make_shared<Text>(1150.f, 164.f, false);
    scoreText2->loadFromText((scoreManager.getScore() == 0 ? "" : std::to_string(scoreManager.getScore())) + "0", clr, this->windowRenderer_, this->font_);
    scoreText2->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> tipText1 = std::make_shared<Text>(850.f, 226.f);
    tipText1->loadFromText(*this->lang_ == Language::ENGLISH ? "Controls: " : u8"Sterowanie: ", clr, this->windowRenderer_, this->font_);
    tipText1->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> tipText2 = std::make_shared<Text>(850.f, 292.f);
    tipText2->loadFromText(*this->lang_ == Language::ENGLISH ? "[W/S/A/D] - move" : u8"[W/S/A/D] - ruch", clr, this->windowRenderer_, this->font_);
    tipText2->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> tipText3 = std::make_shared<Text>(850.f, 356.f);
    tipText3->loadFromText(*this->lang_ == Language::ENGLISH ? "[K] - shoot" : u8"[K] - strza³", clr, this->windowRenderer_, this->font_);
    tipText3->render(0, 0, this->windowRenderer_);

    std::shared_ptr<Text> anyKeyTest = std::make_shared<Text>(850.f, 482.f);
    anyKeyTest->loadFromText(*this->lang_ == Language::ENGLISH ? "Press any key to start" : u8"Nacinij dowolny przycisk, aby zacz¹æ", clr, this->windowRenderer_, this->font_);
    if (isWaitingToStart) { anyKeyTest->render(0, 0, this->windowRenderer_); }
}

void Stage::renderHearts() {
    for (int it = 0; it < this->player_->getHp(); ++it) {
        std::shared_ptr<Renderable> heart = std::make_shared<Renderable>(950.f + 42 * it, 32.f);
        heart->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/life.png", this->windowRenderer_);
        heart->render(0, 0, this->windowRenderer_);
    }

    std::shared_ptr<Renderable> banner = std::make_shared<Renderable>(800.f, 693.f);
    banner->loadFromFile(1.f, 1.f, 1, 1, 1, *this->lang_ == Language::ENGLISH ? "assets/others/bannerEN.png" : "assets/others/bannerPL.png", this->windowRenderer_);
    banner->render(0, 0, this->windowRenderer_);
}

void Stage::waitToStart() {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_KEYDOWN: {
            isWaitingToStart = false;
            break;
        }
        default: {
            break;
        }
        }
    }

    std::shared_ptr<Renderable> banner = std::make_shared<Renderable>(800.f, 693.f);
    banner->loadFromFile(1.f, 1.f, 1, 1, 1, *this->lang_ == Language::ENGLISH ? "assets/others/bannerEN.png" : "assets/others/bannerPL.png", this->windowRenderer_);
    banner->render(0, 0, this->windowRenderer_);
}

Stage::Stage() { this->init(); }

Stage::~Stage() {}

void Stage::loadRenderer(SDL_Renderer* renderer) { this->windowRenderer_ = renderer; }

void Stage::loadFont(TTF_Font* font) { this->font_ = font; }

void Stage::loadLanguage(engine::Language* lang) { this->lang_ = lang; }

std::int8_t Stage::run() {
    if (isWaitingToStart) {
        waitToStart();
        return 0;
    }
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

        if (*keyActions.begin() == input::KeyAction::shootBullet && this->player_->getUpdateFrameCounter() > (this->player_->getPowerup() < 10 ? 12 : this->player_->getPowerup() < 30 ? 6 : 4)) {
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
        case SDL_KEYDOWN: {
            std::list<input::KeyAction> keyActions = keyboard.interpretSingleAction();

            if (*keyActions.begin() == input::KeyAction::useInstinct) { keyActions.pop_front(); }
            if (*keyActions.begin() == input::KeyAction::changeLanguage) { 
                if (*this->lang_ == Language::ENGLISH) { *this->lang_ = Language::POLISH; }
                else if (*this->lang_ == Language::POLISH) { *this->lang_ = Language::ENGLISH; }
                keyActions.pop_front(); 
            }
            break;
        }
        default: {
            break;
        }
        }
    }

    if (enableShooting) {
        if (this->player_->getPowerup() < 20 || this->player_->getPowerup() >= 40) {
            std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(this->player_->X() - 4 + this->player_->W() / 2, this->player_->Y(), playerBulletCenterMovement);
            bullet->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->windowRenderer_);
            bullet->setHitboxRadius(bullet->W() / 2);
            renderableManager.addCollisionable(bullet);
        }
        if (this->player_->getPowerup() >= 20) {
            std::shared_ptr<Bullet> bullet1 = std::make_shared<Bullet>(this->player_->X() - 16 + this->player_->W() / 2, this->player_->Y(), this->player_->getPowerup() < 40 ? playerBulletCenterMovement : playerBulletLeftMovement);
            std::shared_ptr<Bullet> bullet2 = std::make_shared<Bullet>(this->player_->X() + 8 + this->player_->W() / 2, this->player_->Y(), this->player_->getPowerup() < 40 ? playerBulletCenterMovement : playerBulletRightMovement);
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
    scoreManager.setMultiplier(this->player_->getPowerup() / 10);

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
