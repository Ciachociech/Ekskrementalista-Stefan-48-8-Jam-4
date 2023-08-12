#include "engine/Collisionable.h"

namespace engine {

Collisionable::Collisionable(CollisionEntityType type) : Renderable(0, 0), type_(type) {}

Collisionable::Collisionable(float x, float y, CollisionEntityType type) : Renderable(x, y), type_(type) {}

Collisionable::~Collisionable() {}

float Collisionable::hitboxCenterX() { return this->hitboxCenterX_; }

float Collisionable::hitboxCenterY() { return this->hitboxCenterY_; }

float Collisionable::hitboxR() { return this->hitboxRadius_; }

CollisionEntityType Collisionable::getType() { return this->type_; }

std::int8_t Collisionable::getHp() { return this->hp_; }

void Collisionable::setHitboxCenter(float x, float y) {
	this->hitboxCenterX_ = x;
	this->hitboxCenterY_ = y;
}
 
void Collisionable::setHitboxRadius(float radius) { this->hitboxRadius_ = radius; }

bool Collisionable::damage(std::int8_t hpDamage) {
	this->hp_ -= hpDamage;
	return this->hp_ <= 0;
}

}