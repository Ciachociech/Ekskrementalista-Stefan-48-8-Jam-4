#include "engine/Player.h"

namespace engine {

Player::Player(float x, float y) : Collisionable(x, y, CollisionEntityType::PLAYER), powerup_(0) {
	this->setHitboxRadius(12);
	Collisionable::damage(-4);
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
	if (this->Y() + moveY < 100.f) { moveY = 100 -this->Y(); }
	else if (this->Y() + this->H() + moveY > 800.f) { moveY = 800 - this->Y() - this->H(); }
	Renderable::update(moveX, moveY);
	this->setHitboxCenter(X() + W() / 2, Y() + H() / 2);

	this->velX_ *= 0.8;
	this->velY_ *= 0.8;
}

bool Player::damage(std::int8_t hpDamage) {
	if (hpDamage < 0) { 
		switch (hpDamage) {
		case -1: { this->powerup_ += this->powerup_ < 40 ? 1 : 0; break; }
		default: { this->powerup_ += this->powerup_ < 40 ? 2 : 0; break; }
		}
		return true;
	}
	this->powerup_ = this->powerup_ > 10 ? this->powerup_ - 10 : 0;
	Collisionable::damage(hpDamage);
	return false;
}

std::uint8_t Player::getPowerup() {
	return this->powerup_;
}

} // namespace engine
