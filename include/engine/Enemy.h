#ifndef ENGINE_ENEMY_H_
#define ENGINE_ENEMY_H_

#include <functional>

#include "Renderable.h"

namespace engine {



class Enemy : public Renderable {
private:
	std::function<void(float& x, float& y)> movementPattern_;
public:
	Enemy(float x, float y, std::function<void(float& x, float& y)> movementPattern);
	virtual ~Enemy();

	void update(float x, float y) override;
};

}

#endif // !ENGINE_ENEMY_H_
