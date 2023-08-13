#include "managers/RenderableManager.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "utils/MovementPatterns.h"

#include "engine/Enemy.h"
#include "engine/Powerup.h"

namespace managers {

namespace {

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
	srand(time(NULL));
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
							this->collisionables_[it1]->damage((std::int8_t)(type2));
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
							if (!(rand() % 4)) {
								std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupSlowMovement, engine::CollisionEntityType::POWERUP);
								powerup->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/powerup-plus.png", this->renderer_);
								powerup->setHitboxRadius(powerup->W());
								this->addCollisionable(powerup);
							}
						}
						else if (type2 == engine::CollisionEntityType::BOSS) {
							toRemove[it1] = true;

							auto powerupSeed = rand() % 16;
							engine::CollisionEntityType powerupType;
							std::string powerupPath;
							if (powerupSeed > 12 && this->collisionables_[it2]->damage(1)) {
								printf("Hello");
								switch (powerupSeed) {
									case 13: { 
										powerupType = engine::CollisionEntityType::CARROT;
										powerupPath = "assets/sprites/carrot.png";
										break; 
									}
									case 14: { 
										powerupType = engine::CollisionEntityType::BANANA; 
										powerupPath = "assets/sprites/banana.png";
										break; 
									}
									case 15: {
										powerupType = engine::CollisionEntityType::BROCCOLI; 
										powerupPath = "assets/sprites/broccoli.png";
										break; 
									}
									default: { 
										powerupType = engine::CollisionEntityType::POWERUP; 
										powerupPath = "assets/sprites/powerup-plus.png";
										break; 
									}
								}
								std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupFastMovement, powerupType);
								powerup->loadFromFile(1.f, 1.f, 1, 1, 1, powerupPath, this->renderer_);
								powerup->setHitboxRadius(powerup->W());
								this->addCollisionable(powerup);
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
							if (!(rand() % 4)) {
								std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupSlowMovement, engine::CollisionEntityType::POWERUP);
								powerup->loadFromFile(1.f, 1.f, 1, 1, 1, "assets/sprites/powerup-plus.png", this->renderer_);
								powerup->setHitboxRadius(powerup->W());
								this->addCollisionable(powerup);
							}
						}
						break;
					}

					case engine::CollisionEntityType::POWERUP: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it1]->damage(-1);
							toRemove[it2] = true;
						}
						break;
					}
					case engine::CollisionEntityType::CARROT: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it1]->damage(-2);
							toRemove[it2] = true;
						}
						break;
					}
					case engine::CollisionEntityType::BANANA: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it1]->damage(-3);
							toRemove[it2] = true;
						}
						break;
					}
					case engine::CollisionEntityType::BROCCOLI: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it1]->damage(-4);
							toRemove[it2] = true;
						}
						break;
					}

					case engine::CollisionEntityType::BOSS: {
						if (type2 == engine::CollisionEntityType::PLAYER) {
							this->collisionables_[it2]->damage(1);
						} 
						else if (type2 == engine::CollisionEntityType::ALLY_BULLET) {
							toRemove[it2] = true;

							auto powerupSeed = rand() % 16;
							engine::CollisionEntityType powerupType;
							std::string powerupPath;
							if (powerupSeed > 12 && this->collisionables_[it1]->damage(1)) {
								switch (powerupSeed) {
								case 13: {
									powerupType = engine::CollisionEntityType::CARROT;
									powerupPath = "assets/sprites/carrot.png";
									break;
								}
								case 14: {
									powerupType = engine::CollisionEntityType::BANANA;
									powerupPath = "assets/sprites/banana.png";
									break;
								}
								case 15: {
									powerupType = engine::CollisionEntityType::BROCCOLI;
									powerupPath = "assets/sprites/broccoli.png";
									break;
								}
								default: {
									powerupType = engine::CollisionEntityType::POWERUP;
									powerupPath = "assets/sprites/powerup-plus.png";
									break;
								}
								}
								std::shared_ptr<engine::Powerup> powerup = std::make_shared<engine::Powerup>(this->collisionables_[it2]->X() - 12 + this->collisionables_[it2]->W() / 2, this->collisionables_[it2]->Y() + this->collisionables_[it2]->H(), powerupFastMovement, powerupType);
								powerup->loadFromFile(1.f, 1.f, 1, 1, 1, powerupPath, this->renderer_);
								powerup->setHitboxRadius(powerup->W());
								this->addCollisionable(powerup);
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
	
	for (auto it = this->renderables_.begin(); it != this->renderables_.end(); ++it) {
		(*it)->update(0, 0);
	}

	std::shared_ptr<engine::Enemy> enemy;
	for (auto it = this->collisionables_.begin(); it != this->collisionables_.end(); ++it) {
		if ((*it)->getType() == engine::CollisionEntityType::PLAYER) { continue; }
		(*it)->update(0, 0);
		if ((*it)->getType() == engine::CollisionEntityType::BOSS && (*it)->getUpdateFrameCounter() > 30) {
			srand(time(NULL));
			
			std::uint8_t firingRate = 10;
			if ((*it)->getUpdateFrameCounter() < 150) { firingRate = 60; }
			else if ((*it)->getUpdateFrameCounter() < 300) { firingRate = 45; }
			else if ((*it)->getUpdateFrameCounter() < 450) { firingRate = 30; }
			else if ((*it)->getUpdateFrameCounter() < 900) { firingRate = 25; }
			else if ((*it)->getUpdateFrameCounter() < 1800) { firingRate = 20; }
			else if ((*it)->getUpdateFrameCounter() < 3600) { firingRate = 15; }
			
			if ((*it)->getUpdateFrameCounter() % firingRate == 1) { 
				std::uint8_t enemy_type = rand() % 3;
				std::string enemy_model;
				switch (enemy_type) {
					case 0: { enemy_model = "assets/sprites/small-enemy.png"; break; }
					case 1: { enemy_model = "assets/sprites/medium-enemy.png"; break; }
					case 2: { enemy_model = "assets/sprites/big-enemy.png"; break; }
					default: { break; }
				}
				enemy = std::make_shared<engine::Enemy>(rand() * (*it)->getUpdateFrameCounter() % (800 - (16 + 8 * enemy_type)), 64, enemy_type == 0 ? enemySmallMovement : (enemy_type == 1 ? enemyMediumMovement : enemyBigMovement));
				enemy->loadFromFile(1.f, 1.f, 1, 1, 1, enemy_model, this->renderer_);
				enemy->setHitboxRadius(enemy->W() / 2);
			}
		}
	}
	
	if (enemy) { this->addCollisionable(enemy); }

	this->checkCollision();
}

}


