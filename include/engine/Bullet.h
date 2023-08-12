#ifndef ENGINE_BULLET_H_
#define ENGINE_BULLET_H_

#include <functional>

#include "Collisionable.h"
#include "Renderable.h"

namespace engine {

class Bullet : public Renderable, public Collisionable {
private:
	std::function<void(float& x, float& y)> movementPattern_;
public:
	Bullet(float x, float y, bool isHostile, std::function<void(float& x, float& y)> movementPattern);
	virtual ~Bullet();

	void update(float x, float y) override;
	void render(int cameraX, int cameraY, SDL_Renderer* renderer) override;
};

}

#endif // !ENGINE_BULLET_H_
