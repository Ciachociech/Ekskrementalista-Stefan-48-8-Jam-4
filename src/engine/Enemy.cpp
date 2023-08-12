#include "engine/Enemy.h"

namespace engine {

Enemy::Enemy(float x, float y, std::function<void(float& x, float& y)> movementPattern) : Collisionable(x, y, CollisionEntityType::ENEMY), movementPattern_(movementPattern) {
	this->setHitboxCenter(x + (W() / 2), y + (H() / 2));
	this->setHitboxRadius(H() / 2);
}

Enemy::~Enemy() {}

void Enemy::update(float x, float y) {
	float moveX = 0;
	float moveY = 0;

	this->movementPattern_(moveX, moveY);
	Renderable::update(moveX, moveY);
	this->setHitboxCenter(X() + W() / 2, Y() + H() / 2);
}

bool Enemy::damage(std::int8_t hpDamage) {
	return Collisionable::damage(hpDamage);
}

}


