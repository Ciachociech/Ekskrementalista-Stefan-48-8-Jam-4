#include "managers/RenderableManager.h"

#include <cmath>

namespace managers {

void RenderableManager::clean() {
	for (auto it = this->renderables_.begin(); it != this->renderables_.end();) {
		bool isOutside = (*it)->X() < -2 * (*it)->W() || (*it)->X() > 800 + 2 * (*it)->W() ||
			(*it)->Y() < -2 * (*it)->H() || (*it)->Y() > 800 + 2 * (*it)->H();
		if (isOutside) {
			it = this->renderables_.erase(it);
		} else {
			++it;
		}
	}
}

void RenderableManager::checkCollision() {
	for (auto it1 = this->collisionables_.begin(); it1 != this->collisionables_.end(); ++it1) {
		for (auto it2 = it1 + 1; it2 != this->collisionables_.end(); ++it2) {
			engine::CollisionEntityType type1 = (*it1)->getType();
			engine::CollisionEntityType type2 = (*it2)->getType();
			switch (type1) {
			case engine::CollisionEntityType::PLAYER: {
				if ((type2 == engine::CollisionEntityType::ENEMY || type2 == engine::CollisionEntityType::ENEMY_BULLET) && this->checkCollision(*it1, *it2)) {
					it2 = this->collisionables_.erase(it2);
				}
				break;
			}
			case engine::CollisionEntityType::ALLY_BULLET: {
				if (type2 == engine::CollisionEntityType::ENEMY && this->checkCollision(*it1, *it2)) {
					it1 = this->collisionables_.erase(it1);
					it2 = this->collisionables_.erase(it2);
				}
				break;
			}
			case engine::CollisionEntityType::ENEMY: {
				if ((type2 == engine::CollisionEntityType::PLAYER || type2 == engine::CollisionEntityType::ALLY_BULLET) && this->checkCollision(*it1, *it2)) {
					it1 = this->collisionables_.erase(it1);
					it2 = this->collisionables_.erase(it2);
				}
				break;
			}
			case engine::CollisionEntityType::ENEMY_BULLET:
				if (type2 == engine::CollisionEntityType::PLAYER && this->checkCollision(*it1, *it2)) {
					it1 = this->collisionables_.erase(it1);
					it2 = this->collisionables_.erase(it2);
				}
				break;
			default: { break; }
			}
		}
	}
}

bool RenderableManager::checkCollision(std::shared_ptr<engine::Collisionable> lhs, std::shared_ptr<engine::Collisionable> rhs) {
	float distX = lhs->hitboxCenterX() - rhs->hitboxCenterX();
	float distY = lhs->hitboxCenterY() - rhs->hitboxCenterY();
	float dist = std::sqrt(distX * distX + distY * distY);
	float radiusSum = lhs->hitboxR() + rhs->hitboxR();
	return dist < radiusSum;
}

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
	for (auto& collisionable : this->collisionables_) {
		collisionable->render(0, 0, this->renderer_);
	}
}

void RenderableManager::addRenderable(std::shared_ptr<engine::Renderable> renderable) {
	this->renderables_.push_back(renderable);
}

void RenderableManager::addCollisiionable(std::shared_ptr<engine::Collisionable> collisionable) {
	this->collisionables_.push_back(collisionable);
}

void RenderableManager::update() {
	if (this->renderables_.size() > 1) {
		this->clean();
	}
	//ignore first element (so now), because of player instance
	for (auto it = ++this->renderables_.begin(); it != this->renderables_.end(); ++it) {
		(*it)->update(0, 0);
	}
}

}


