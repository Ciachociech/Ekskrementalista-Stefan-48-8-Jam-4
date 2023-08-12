#include "managers/CollisionManager.h"

#include <cmath>

namespace managers {

	CollisionManager::CollisionManager() : collisionables_() {}

	bool CollisionManager::checkCollision(std::shared_ptr<engine::Collisionable> lhs, std::shared_ptr<engine::Collisionable> rhs) {
		float distX = lhs->centerX() - rhs->centerX();
		float distY = lhs->centerY() - rhs->centerY();
		float dist = std::sqrt(distX * distX + distY * distY);
		float radiusSum = lhs->R() + rhs->R();
		return dist < radiusSum;
	}

	CollisionManager& CollisionManager::instance() {
		static CollisionManager collisionManager;
		return collisionManager;
	}

	CollisionManager::~CollisionManager() {}

	void CollisionManager::update() {
		for (auto it1 = this->collisionables_.begin(); it1 != this->collisionables_.end(); ++it1) {
			for (auto it2 = it1+1; it2 != this->collisionables_.end(); ++it2) {
				engine::CollisionEntityType type1 = (*it1)->getType();
				engine::CollisionEntityType type2 = (*it2)->getType();
				switch (type1) {
				case engine::CollisionEntityType::PLAYER: {
					if ((type2 == engine::CollisionEntityType::ENEMY || type2 == engine::CollisionEntityType::ENEMY_BULLET) && this->checkCollision(*it1, *it2)) {
						(*it2)->~Collisionable();
						it2 = this->collisionables_.erase(it2);
					}
					break;
				}
				case engine::CollisionEntityType::ALLY_BULLET: {
					if (type2 == engine::CollisionEntityType::ENEMY && this->checkCollision(*it1, *it2)) {
						it1->reset();
						it2->reset();
						it1 = this->collisionables_.erase(it1);
						it2 = this->collisionables_.erase(it2);
					}
					break;
				}
				case engine::CollisionEntityType::ENEMY: {
					if ((type2 == engine::CollisionEntityType::PLAYER || type2 == engine::CollisionEntityType::ALLY_BULLET) && this->checkCollision(*it1, *it2)) {
						it1->reset();
						it2->reset();
						it1 = this->collisionables_.erase(it1);
						it2 = this->collisionables_.erase(it2);
					}
					break;
				}
				case engine::CollisionEntityType::ENEMY_BULLET:
					if (type2 == engine::CollisionEntityType::PLAYER && this->checkCollision(*it1, *it2)) {
						it1->reset();
						it2->reset();
						it1 = this->collisionables_.erase(it1);
						it2 = this->collisionables_.erase(it2);
					}
					break;
				default: { break; }
				}
			}
		}

	}

void CollisionManager::addCollisionable(std::shared_ptr<engine::Collisionable> collisionable) {
	this->collisionables_.push_back(collisionable);
}

}