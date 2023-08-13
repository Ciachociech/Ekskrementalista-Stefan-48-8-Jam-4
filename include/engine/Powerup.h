#ifndef ENGINE_POWERUP_H_
#define ENGINE_POWERUP_H_

#include <functional>

#include "Collisionable.h"

namespace engine {

class Powerup : public Collisionable {
private:
	std::function<void(float& x, float& y)> movementPattern_;
public:
	Powerup(float x, float y, std::function<void(float& x, float& y)> movementPattern, CollisionEntityType type);
	virtual ~Powerup();

	void update(float x, float y) override;
	bool damage(std::int8_t hpDamage) override;
};

}

#endif // !ENGINE_POWERUP_H_
