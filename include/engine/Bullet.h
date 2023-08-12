#ifndef ENGINE_BULLET_H_
#define ENGINE_BULLET_H_

#include <functional>

#include "Collisionable.h"

namespace engine {

class Bullet : public Collisionable {
private:
	std::function<void(float& x, float& y)> movementPattern_;
public:
	Bullet(float x, float y, std::function<void(float& x, float& y)> movementPattern);
	virtual ~Bullet();

	void update(float x, float y) override;
	bool damage(std::int8_t hpDamage) override;
};

}

#endif // !ENGINE_BULLET_H_
