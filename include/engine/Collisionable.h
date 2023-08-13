#ifndef ENGINE_COLLISIONABLE_H_
#define ENGINE_COLLISIONABLE_H_

#include "Renderable.h"

namespace engine {

enum class CollisionEntityType {
	PLAYER = 0, ALLY_BULLET = 1, ENEMY = 2, BOSS = 6, POWERUP = -1, CARROT = -2, BANANA = -3, BROCCOLI = -4
};

class Collisionable : public Renderable {
private:
	float hitboxCenterX_;
	float hitboxCenterY_;
	float hitboxRadius_;
	CollisionEntityType type_;
	std::int8_t hp_;
public:
	Collisionable(CollisionEntityType type);
	Collisionable(float x, float y, CollisionEntityType type);
	virtual ~Collisionable();

	float hitboxCenterX();
	float hitboxCenterY();
	float hitboxR();
	CollisionEntityType getType();
	std::int8_t getHp();

	void setHitboxCenter(float x, float y);
	void setHitboxRadius(float radius);

	virtual bool damage(std::int8_t hpDamage);
};

}

#endif // !ENGINE_COLLISIONABLE_H_

