#include "engine/Bullet.h"

namespace engine {
	
Bullet::Bullet(float x, float y, bool isHostile, std::function<void(float& x, float& y)> movementPattern) : Renderable(x, y), Collisionable(isHostile ? CollisionEntityType::ENEMY_BULLET : CollisionEntityType::ALLY_BULLET), movementPattern_(movementPattern) {
	this->setCenter(x + (W() / 2), y + (H() / 2));
	this->setRadius(H() / 2);
}

Bullet::~Bullet() {}

void Bullet::update(float x, float y) {
	float moveX = 0;
	float moveY = 0;

	this->movementPattern_(moveX, moveY);
	Renderable::update(moveX, moveY);
	this->setCenter(X() + W() / 2 + moveX, Y() + H() / 2 + moveY);
}



}