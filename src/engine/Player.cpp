#include "engine/Player.h"

namespace engine {

Player::Player(float x, float y): Renderable(x, y) {}

Player::~Player() {}

void Player::move(float x, float y) {
	float moveX = this->velX_ + 0.5 * this->accX_;
	float moveY = this->velY_ + 0.5 * this->accY_;
	Renderable::move(moveX, moveY);

	this->velX_ = 0.3 * this->accX_ + 0.7 * this->velX_;
	this->velY_ = 0.3 * this->accY_ + 0.7 * this->velY_;
	float speedRatio = std::sqrt(this->velX_ * this->velX_ + this->velY_ * this->velY_) / maxSpeed;
	if (speedRatio > 1.f) {
		this->velX_ /= speedRatio;
		this->velY_ /= speedRatio;
	}

	this->accX_ = x;
	this->accY_ = y;
	if (this->accX_ > maxAcc) { this->accX_ = maxAcc; }
	if (this->accY_ > maxAcc) { this->accY_ = maxAcc; }
}

} // namespace engine
