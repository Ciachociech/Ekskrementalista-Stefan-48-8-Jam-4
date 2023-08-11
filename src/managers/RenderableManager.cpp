#include "managers/RenderableManager.h"

namespace managers {

RenderableManager::RenderableManager(SDL_Renderer* renderer) : renderer_(renderer), renderables_() {}

RenderableManager& RenderableManager::instance(SDL_Renderer* renderer) {
	static RenderableManager renderableManager(renderer);
	return renderableManager;
}

RenderableManager::~RenderableManager() { this->renderables_.clear(); }

void RenderableManager::render() {
	for (auto& renderable : this->renderables_) { 
		renderable->render(0, 0, this->renderer_); 
	}
}

void RenderableManager::clean() {
	for (auto it = this->renderables_.begin(); it != this->renderables_.end(); ++it) {
		bool isOutside = (*it)->X() < -2 * (*it)->W() || (*it)->X() > 800 + 2 * (*it)->W() ||
			(*it)->Y() < -2 * (*it)->H() || (*it)->Y() > 800 + 2 * (*it)->H();
		if (isOutside) {
			this->renderables_.erase(it);
		}
	}
}

void RenderableManager::addRenderable(engine::Renderable* renderable) {
	this->renderables_.push_back(renderable);
}

}


