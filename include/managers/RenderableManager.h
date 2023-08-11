#ifndef MANAGERS_RENDERABLEMANAGER_H_
#define MANAGERS_RENDERABLEMANAGER_H_

#include <memory>
#include <vector>

#include "engine/Renderable.h"

namespace managers {

class RenderableManager {
private:
	SDL_Renderer* renderer_;

	std::vector<engine::Renderable*> renderables_;

	RenderableManager(SDL_Renderer* renderer);
public:
	RenderableManager(const RenderableManager& /*original*/) = delete;
	RenderableManager& operator=(const RenderableManager& /*object*/) = delete;

	static RenderableManager& instance(SDL_Renderer* renderer = NULL);
	virtual ~RenderableManager();

	void render();
	void clean();

	void addRenderable(engine::Renderable* renderable);
};

}

#endif // !MANAGERS_RENDERABLEMANAGER_H_
