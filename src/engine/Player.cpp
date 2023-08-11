#include "engine/Player.h"

namespace engine {

Player::Player(float x, float y): Renderable(x, y) {}

Player::~Player() {}

void Player::move(float x, float y) {
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
	Renderable::move(moveX, moveY);

	this->velX_ *= 0.8;
	this->velY_ *= 0.8;
}

} // namespace engine
