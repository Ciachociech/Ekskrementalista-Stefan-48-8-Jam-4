#ifndef ENGINE_PLAYER_H_
#define ENGINE_PLAYER_H_

#include "Renderable.h"

namespace engine {

class Player: public Renderable {
private:
public:
    Player(int x, int y);
    virtual ~Player();
};

} // namespace engine

#endif // !ENGINE_PLAYER_H_
