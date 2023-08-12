#include "engine/Enemy.h"

namespace enemy {

}

engine::Enemy::Enemy(float x, float y, std::function<void(float& x, float& y)> movementPattern) : Renderable(x, y), movementPattern_(movementPattern) {}

engine::Enemy::~Enemy() {}

void engine::Enemy::update(float x, float y) {
	float movX = 0;
	float movY = 0;

	this->movementPattern_(movX, movY);
	Renderable::update(movX, movY);
}
