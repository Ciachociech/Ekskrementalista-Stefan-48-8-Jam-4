#include "engine/Collisionable.h"

namespace engine {

Collisionable::Collisionable(float xCenter, float yCenter, float radius, CollisionEntityType type) : xCenter_(xCenter), yCenter_(yCenter), radius_(radius), type_(type) {}

Collisionable::~Collisionable() {}

float Collisionable::centerX() { return this->xCenter_; }

float Collisionable::centerY() { return this->yCenter_; }

float Collisionable::R() { return this->radius_; }

CollisionEntityType Collisionable::getType() { return this->type_; }

}