#include "engine/Player.h"

namespace engine {

Player::Player(float x, float y): Renderable(x, y), Collisionable(CollisionEntityType::PLAYER) {
    this->setCenter(x + (W() / 2), y + (H() / 2));
    this->setRadius(12);
}

Player::~Player() {}

void Player::update(float x, float y) {
	this->accX_ = x;
	this->accY_ = y;

	this->velX_ += this->accX_;
	this->velY_ += this->accY_;
	float speedRatio = std::sqrt(this->velX_ * this->velX_ + this->velY_ * this->velY_) / maxSpeed;
	if (speedRatio > 1.f) {
		this->velX_ /= speedRatio;
		this->velY_ /= speedRatio;
	}

	float moveX = this->velX_;
	float moveY = this->velY_;
	if (this->X() + moveX < 0.f) { moveX = -this->X(); }
	else if (this->X() + this->W() + moveX > 800.f) { moveX = 800 - this->X() - this->W(); }
	if (this->Y() + moveY < 0.f) { moveY = -this->Y(); }
	else if (this->Y() + this->H() + moveY > 800.f) { moveY = 800 - this->Y() - this->H(); }
	Renderable::update(moveX, moveY);
    this->setCenter(X() + W() / 2 + moveX, Y() + H() / 2 + moveY);

	this->velX_ *= 0.8;
	this->velY_ *= 0.8;
}

void Player::render(int cameraX, int cameraY, SDL_Renderer* renderer) {
    Renderable::render(cameraX, cameraY, renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const float diameter = (R() * 2);

    int32_t x = (R() - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centerX() + x, centerY() - y);
        SDL_RenderDrawPoint(renderer, centerX() + x, centerY() + y);
        SDL_RenderDrawPoint(renderer, centerX() - x, centerY() - y);
        SDL_RenderDrawPoint(renderer, centerX() - x, centerY() + y);
        SDL_RenderDrawPoint(renderer, centerX() + y, centerY() - x);
        SDL_RenderDrawPoint(renderer, centerX() + y, centerY() + x);
        SDL_RenderDrawPoint(renderer, centerX() - y, centerY() - x);
        SDL_RenderDrawPoint(renderer, centerX() - y, centerY() + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

} // namespace engine
