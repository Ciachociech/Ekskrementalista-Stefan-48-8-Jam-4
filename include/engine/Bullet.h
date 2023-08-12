#ifndef ENGINE_BULLET_H_
#define ENGINE_BULLET_H_

#include <functional>

#include "Renderable.h"

namespace engine {

class Bullet : public Renderable {
private:
	bool isHostile_;
	std::function<void(float& x, float& y)> movementPattern_;
public:
	Bullet(float x, float y, bool isHostile, std::function<void(float& x, float& y)> movementPattern);
	virtual ~Bullet();

	void move(float x, float y) override;
};

}

#endif // !ENGINE_BULLET_H_
