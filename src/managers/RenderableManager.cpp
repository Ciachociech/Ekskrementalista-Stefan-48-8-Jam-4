#include "managers/RenderableManager.h"

#include <cmath>

#include "engine/Powerup.h"

namespace managers {

namespace {

void powerupSlowMovement(float& x, float& y) {
	x = 0.f;
	y = 1.f;
}

void powerupFastMovement(float& x, float& y) {
	x = 0.f;
	y = 2.f;
}

}

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
	for (auto it = this->collisionables_.begin(); it != this->collisionables_.end();) {
		bool isOutside = (*it)->X() < -2 * (*it)->W() || (*it)->X() > 800 + 2 * (*it)->W() ||
			(*it)->Y() < -2 * (*it)->H() || (*it)->Y() > 800 + 2 * (*it)->H();
		if (isOutside) {
			it = this->collisionables_.erase(it);
		}
		else {
			++it;
		}
	}
}

void RenderableManager::checkCollision() {
	auto currentSize = this->collisionables_.size();
	std::vector<bool> toRemove(currentSize, false);

	for (auto it1 = 0; it1 < currentSize; ++it1) {
		for (auto it2 = it1 + 1; it2 < currentSize; ++it2) {
			if (this->checkCollision(this->collisionables_[it1], this->collisionables_[it2])) {
				engine::CollisionEntityType type1 = this->collisionables_[it1]->getType();
				engine::CollisionEntityType type2 = this->collisionables_[it2]->getType();
				switch (type1) {
					case engine::CollisionEntityType::PLAYER: {
						if (type2 == engine::CollisionEntityType::ENEMY) {
							this->collisionables_[it1]->damage(1);
							toRemove[it2] = true;
						}
						else if ((std::int8_t)(type2) < 0) {
							this->collisionables_[it1]->damage(-1);
							toRemove[it2] = true;
						}
						else if (type2 == engine::CollisionEntityType::BOSS) {
							this->collisionables_[it1]->damage(1);
						}
						break;
					}

					case engine::CollisionEntityType::ALLY_BULLET: {
						if (type2 == engine::CollisionEntityType::ENEMY) {
							toRemove[it1] = true;
							toRemove[it2] = true;
							if (!(this->collisionables_[it2]->getUpdateFrameCounter() % 4)) {
								std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupSlowMovement, engine::CollisionEntityType::POWERUP);
								powerup->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->renderer_);
								powerup->setHitboxRadius(powerup->W() / 2);
								this->addCollisionable(powerup);
							}
						}
						else if (type2 == engine::CollisionEntityType::BOSS) {
							toRemove[it1] = true;
							this->collisionables_[it2]->damage(1);

							auto powerupSeed = this->collisionables_[it2]->getUpdateFrameCounter() % 16;
							engine::CollisionEntityType powerupType;
							if (powerupSeed > 12) {
								switch (powerupSeed) {
									case 13: { powerupType = engine::CollisionEntityType::CARROT; break; }
									case 14: { powerupType = engine::CollisionEntityType::BANANA; break; }
									case 15: { powerupType = engine::CollisionEntityType::BROCCOLI; break; }
									default: { powerupType = engine::CollisionEntityType::POWERUP; break; }
								}
								//std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupFastMovement, powerupSeed);
								//powerup->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->renderer_);
								//powerup->setHitboxRadius(powerup->W() / 2);
								//this->addCollisionable(powerup);
							}
						}
						break;
					}

					case engine::CollisionEntityType::ENEMY: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							toRemove[it1] = true;
							this->collisionables_[it2]->damage(1);
						} 
						else if (type2 == engine::CollisionEntityType::ALLY_BULLET) {
							toRemove[it1] = true;
							toRemove[it2] = true;
							if (!(this->collisionables_[it2]->getUpdateFrameCounter() % 4)) {
								std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupSlowMovement, engine::CollisionEntityType::POWERUP);
								powerup->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->renderer_);
								powerup->setHitboxRadius(powerup->W() / 2);
								this->addCollisionable(powerup);
							}
						}
						break;
					}

					case engine::CollisionEntityType::POWERUP:
					case engine::CollisionEntityType::CARROT: 
					case engine::CollisionEntityType::BANANA: 
					case engine::CollisionEntityType::BROCCOLI: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it1]->damage(-1);
							toRemove[it2] = true;
						}
						break;
					}

					case engine::CollisionEntityType::BOSS: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it2]->damage(1);
						} 
						else if (type2 == engine::CollisionEntityType::ALLY_BULLET) {
							this->collisionables_[it1]->damage(1);
							toRemove[it2] = true;

							auto powerupSeed = this->collisionables_[it2]->getUpdateFrameCounter() % 16;
							engine::CollisionEntityType powerupType;
							if (powerupSeed > 12) {
								switch (powerupSeed) {
								case 13: { powerupType = engine::CollisionEntityType::CARROT; break; }
								case 14: { powerupType = engine::CollisionEntityType::BANANA; break; }
								case 15: { powerupType = engine::CollisionEntityType::BROCCOLI; break; }
								default: { powerupType = engine::CollisionEntityType::POWERUP; break; }
								}
								//std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupFastMovement, powerupSeed);
								//powerup->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/poop.png", this->renderer_);
								//powerup->setHitboxRadius(powerup->W() / 2);
								//this->addCollisionable(powerup);
							}
						}
						break;
					}
					default: { break; }

				}
			}
		}
	}

	for (std::int16_t it = toRemove.size() - 1; it > -1; --it) {
		if (toRemove[it]) { 
			this->collisionables_.erase(this->collisionables_.begin() + it); 
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

void RenderableManager::addCollisionable(std::shared_ptr<engine::Collisionable> collisionable) {
	this->collisionables_.push_back(collisionable);
}

void RenderableManager::update() {
	if (this->renderables_.size() + this->collisionables_.size() > 1) {
		this->clean();
	}
	//ignore first element (so now), because of player instance
	for (auto it = this->renderables_.begin(); it != this->renderables_.end(); ++it) {
		(*it)->update(0, 0);
	}
	for (auto it = ++this->collisionables_.begin(); it != this->collisionables_.end(); ++it) {
		(*it)->update(0, 0);
	}

	this->checkCollision();
	printf("Number of entities: %d\n", this->collisionables_.size());
}

}


