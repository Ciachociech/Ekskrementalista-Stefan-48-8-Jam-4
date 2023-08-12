#include "engine/Bullet.h"

namespace engine {
	
Bullet::Bullet(float x, float y, bool isHostile, std::function<void(float& x, float& y)> movementPattern) : Renderable(x, y), Collisionable(centerX() + W() / 2, centerY() + H() / 2, H() / 2, isHostile ? CollisionEntityType::ENEMY_BULLET : CollisionEntityType::ALLY_BULLET), movementPattern_(movementPattern) {}

Bullet::~Bullet() {}

void Bullet::update(float x, float y) {
	float movX = 0;
	float movY = 0;

	this->movementPattern_(movX, movY);
	Renderable::update(movX, movY);
}



}