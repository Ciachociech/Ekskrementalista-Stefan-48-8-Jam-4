#ifndef ENGINE_STAGE_H_
#define ENGINE_STAGE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "Renderable.h"

namespace engine {

class Stage {
private:
    // Global SDL values
    SDL_Renderer* windowRenderer_ = NULL;
    TTF_Font* font_ = NULL;

    // Game managers

    // Others
    Renderable renderable;

public:
    Stage();
    virtual ~Stage();

    // loading pointers to instance managers and objects
    void loadRenderer(SDL_Renderer* renderer);
    void loadFont(TTF_Font* font);

    // Game functions
    int run();
    void init();
    void render();
};

} // namespace engine

#endif // !ENGINE_STAGE_H_
