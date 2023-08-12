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

} // namespace engine
