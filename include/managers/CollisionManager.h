#ifndef MANAGERS_COLLISIONMANAGER_H_
#define MANAGERS_COLLISIONMANAGER_H_

#include <memory>
#include <vector>

#include "engine/Collisionable.h"

namespace managers {

class CollisionManager {
private:
	std::vector<std::shared_ptr<engine::Collisionable>> collisionables_;

	CollisionManager();

	bool checkCollision(std::shared_ptr<engine::Collisionable> lhs, std::shared_ptr<engine::Collisionable> rhs);
public:
	CollisionManager(const CollisionManager& /*original*/) = delete;
	CollisionManager& operator=(const CollisionManager& /*object*/) = delete;

	static CollisionManager& instance();
	virtual ~CollisionManager();

	void update();

	void addCollisionable(std::shared_ptr<engine::Collisionable> collisionable);
};

}

#endif // !MANAGERS_COLLISIONMANAGER_H_
