#include "engine/Bullet.h"

namespace engine {
	
Bullet::Bullet(float x, float y, bool isHostile, std::function<void(float& x, float& y)> movementPattern) : Renderable(x, y), isHostile_(isHostile), movementPattern_(movementPattern) {}

Bullet::~Bullet() {}

void Bullet::move(float x, float y) {
	float movX = 0;
	float movY = 0;

	this->movementPattern_(movX, movY);
	Renderable::move(movX, movY);
}



}