#ifndef ENGINE_PLAYER_H_
#define ENGINE_PLAYER_H_

#include <cmath>

#include "Renderable.h"

namespace engine {

namespace {

constexpr float maxSpeed = 5.f;
constexpr float maxAcc = 30.f;

}

class Player: public Renderable {
private:
    float velX_;
    float velY_;
    float accX_;
    float accY_;
public:
    Player(float x, float y);
    virtual ~Player();

    void move(float x, float y) override;
};

} // namespace engine

#endif // !ENGINE_PLAYER_H_
