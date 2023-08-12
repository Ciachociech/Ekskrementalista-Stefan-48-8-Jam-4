#include "engine/Enemy.h"

namespace enemy {

}

engine::Enemy::Enemy(float x, float y, std::function<void(float& x, float& y)> movementPattern) : Renderable(x, y), Collisionable(CollisionEntityType::ENEMY), movementPattern_(movementPattern) {
	this->setCenter(x + (W() / 2), y + (H() / 2));
	this->setRadius(H() / 2);
}

engine::Enemy::~Enemy() {}

void engine::Enemy::update(float x, float y) {
	float moveX = 0;
	float moveY = 0;

	this->movementPattern_(moveX, moveY);
	Renderable::update(moveX, moveY);
	this->setCenter(X() + W() / 2 + moveX, Y() + H() / 2 + moveY);
}
