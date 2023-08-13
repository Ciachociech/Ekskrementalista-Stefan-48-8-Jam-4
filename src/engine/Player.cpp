#include "engine/Player.h"

namespace engine {

Player::Player(float x, float y) : Collisionable(x, y, CollisionEntityType::PLAYER) {
	this->setHitboxCenter(x + (W() / 2), y + (H() / 2));
	this->setHitboxRadius(12);
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
	this->setHitboxCenter(X() + W() / 2, Y() + H() / 2);

	this->velX_ *= 0.8;
	this->velY_ *= 0.8;
}

bool Player::damage(std::int8_t hpDamage) {
	if (hpDamage < 0) { 
		switch (hpDamage) {
			case -1: { this->powerup_ += 1; break; }
			default: { break; }
		}
		return true;
	}
	this->powerup_ = this->powerup_ > 20 ? this->powerup_ - 20 : 0;
	return Collisionable::damage(hpDamage);
}

} // namespace engine
