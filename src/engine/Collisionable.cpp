#include "engine/Collisionable.h"

namespace engine {

Collisionable::Collisionable(CollisionEntityType type) : type_(type) {}

Collisionable::~Collisionable() {}

float Collisionable::centerX() { return this->xCenter_; }

float Collisionable::centerY() { return this->yCenter_; }

float Collisionable::R() { return this->radius_; }

CollisionEntityType Collisionable::getType() { return this->type_; }

void Collisionable::setCenter(float x, float y) {
	this->xCenter_ = x;
	this->yCenter_ = y;
}
 
void Collisionable::setRadius(float radius) { this->radius_ = radius; }

}