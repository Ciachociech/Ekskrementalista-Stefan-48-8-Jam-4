#ifndef ENGINE_COLLISIONABLE_H_
#define ENGINE_COLLISIONABLE_H_

#include "Renderable.h"

namespace engine {

enum class CollisionEntityType {
	PLAYER = 0, ALLY_BULLET = 1, ENEMY = 2, POWERUP = 4, BOSS = 6
};

class Collisionable : public Renderable {
private:
	float hitboxCenterX_;
	float hitboxCenterY_;
	float hitboxRadius_;
	CollisionEntityType type_;
public:
	Collisionable(CollisionEntityType type);
	Collisionable(float x, float y, CollisionEntityType type);
	virtual ~Collisionable();

	float hitboxCenterX();
	float hitboxCenterY();
	float hitboxR();
	CollisionEntityType getType();

	void setHitboxCenter(float x, float y);
	void setHitboxRadius(float radius);
};

}

#endif // !ENGINE_COLLISIONABLE_H_

