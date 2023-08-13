#include "engine/Boss.h"

#include <cstdlib>
#include <ctime>

#include "managers/ScoreManager.h"

namespace engine {

namespace {
	
managers::ScoreManager& scoreManager = managers::ScoreManager::instance();

}

Boss::Boss(float x, float y, std::function<void(float& x, float& y)> movementPattern) : Collisionable(x, y, CollisionEntityType::BOSS), movementPattern_(movementPattern) {}

Boss::~Boss() {}

void Boss::update(float x, float y) {
	float moveX = 0;
	float moveY = 0;

	if (!(this->getUpdateFrameCounter() % 30)) {
		srand(time(NULL));
		this->movementPattern_(moveX, moveY);
		moveX *= rand() % 2 ? -1 : 1;
		if (X() + moveX > 600.f || X() - moveX < 152.f) { moveX = 0; }
	}

	Renderable::update(moveX, moveY);
	scoreManager.increaseScore(1);

	this->setHitboxCenter(X() + W() / 2, Y() + H() / 2);
	this->powerupCooldown_++;
}

bool Boss::damage(std::int8_t hpDamage) {
	if (this->powerupCooldown_ > 60) {
		this->powerupCooldown_ = 0;
		return true;
	}
	return false;
	scoreManager.increaseScore(10 * scoreManager.getMultiplier());
}

}