#include "engine/Powerup.h"

namespace engine {

Powerup::Powerup(float x, float y, std::function<void(float& x, float& y)> movementPattern, CollisionEntityType type) : Collisionable(x, y, type), movementPattern_(movementPattern) {}

Powerup::~Powerup() {}

void Powerup::update(float x, float y) {
	float moveX = 0;
	float moveY = 0;

	this->movementPattern_(moveX, moveY);
	Renderable::update(moveX, moveY);
	this->setHitboxCenter(X() + W() / 2, Y() + H() / 2);
}

bool Powerup::damage(std::int8_t hpDamage) {
	return Collisionable::damage(hpDamage);
}



}