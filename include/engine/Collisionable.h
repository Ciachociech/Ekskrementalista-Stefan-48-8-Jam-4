#ifndef ENGINE_COLLISIONABLE_H_
#define ENGINE_COLLISIONABLE_H_

namespace engine {

enum class CollisionEntityType {
	PLAYER = 0, ALLY_BULLET = 1, ENEMY = 2, ENEMY_BULLET = 3, GHOST_ENEMY = 6
};

class Collisionable {
private:
	float xCenter_;
	float yCenter_;
	float radius_;
	CollisionEntityType type_;
public:
	Collisionable(float xCenter, float yCenter, float radius, CollisionEntityType type);
	virtual ~Collisionable();

	float centerX();
	float centerY();
	float R();
	CollisionEntityType getType();
};

}

#endif // !ENGINE_COLLISIONABLE_H_

