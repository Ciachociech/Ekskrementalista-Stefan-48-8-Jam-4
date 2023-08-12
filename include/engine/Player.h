#ifndef ENGINE_PLAYER_H_
#define ENGINE_PLAYER_H_

#include <cmath>

#include "Collisionable.h"

namespace engine {

namespace {

constexpr float maxSpeed = 4.5f;

}

class Player: public Collisionable {
private:
    float velX_;
    float velY_;
    float accX_;
    float accY_;

    std::uint8_t powerup_;
public:
    Player(float x, float y);
    virtual ~Player();

    void update(float x, float y) override;
    bool damage(std::int8_t hpDamage) override;
};

} // namespace engine

#endif // !ENGINE_PLAYER_H_
