#ifndef MANAGERS_RENDERABLEMANAGER_H_
#define MANAGERS_RENDERABLEMANAGER_H_

#include <memory>
#include <vector>

#include <SDL.h>

#include "engine/Collisionable.h"
#include "engine/Renderable.h"

namespace managers {

class RenderableManager {
private:
	SDL_Renderer* renderer_;

	std::vector<std::shared_ptr<engine::Collisionable>> collisionables_;
	std::vector<std::shared_ptr<engine::Renderable>> renderables_;

	RenderableManager(SDL_Renderer* renderer);

	void clean();
	void checkCollision();
	bool checkCollision(std::shared_ptr<engine::Collisionable> lhs, std::shared_ptr<engine::Collisionable> rhs);
public:
	RenderableManager(const RenderableManager& /*original*/) = delete;
	RenderableManager& operator=(const RenderableManager& /*object*/) = delete;

	static RenderableManager& instance(SDL_Renderer* renderer = NULL);
	virtual ~RenderableManager();

	void render();

	void addRenderable(std::shared_ptr<engine::Renderable> renderable);
	void addCollisionable(std::shared_ptr<engine::Collisionable> collisionable);
	void update();
};

}

#endif // !MANAGERS_RENDERABLEMANAGER_H_
