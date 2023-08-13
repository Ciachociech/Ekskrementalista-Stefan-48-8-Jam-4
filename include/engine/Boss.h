#ifndef ENGINE_BOSS_H_
#define ENGINE_BOSS_H_

#include <functional>

#include "Collisionable.h"

namespace engine {

class Boss : public Collisionable {
private:
	std::function<void(float& x, float& y)> movementPattern_;

	std::uint32_t powerupCooldown_;
public:
	Boss(float x, float y, std::function<void(float& x, float& y)> movementPattern);
	virtual ~Boss();

	void update(float x, float y) override;
	bool damage(std::int8_t hpDamage) override;
};

}

#endif // !ENGINE_BOSS_H_
