#include "engine/Enemy.h"

namespace enemy {

}

engine::Enemy::Enemy(float x, float y, std::function<void(float& x, float& y)> movementPattern) : Collisionable(x, y, CollisionEntityType::ENEMY), movementPattern_(movementPattern) {
	this->setHitboxCenter(x + (W() / 2), y + (H() / 2));
	this->setHitboxRadius(H() / 2);
}

engine::Enemy::~Enemy() {}

void engine::Enemy::update(float x, float y) {
	float moveX = 0;
	float moveY = 0;

	this->movementPattern_(moveX, moveY);
	Renderable::update(moveX, moveY);
	this->setHitboxCenter(X() + W() / 2 + moveX, Y() + H() / 2 + moveY);
}
