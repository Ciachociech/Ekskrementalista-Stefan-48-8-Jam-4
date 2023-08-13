#ifndef ENGINE_STAGE_H_
#define ENGINE_STAGE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>

#include "input/InputKeyboard.h"
#include "managers/RenderableManager.h"
#include "Player.h"

namespace engine {

namespace {

constexpr float playerMovement = 2.5f;

}

class Stage {
private:
    // Global SDL values
    SDL_Renderer* windowRenderer_ = NULL;
    TTF_Font* font_ = NULL;

    // Others
    std::shared_ptr<Player> player_;
    input::InputKeyboard keyboard;
    void renderText();
    void renderHearts();
public:
    Stage();
    virtual ~Stage();

    // loading pointers to instance managers and objects
    void loadRenderer(SDL_Renderer* renderer);
    void loadFont(TTF_Font* font);

    // Game functions
    std::int8_t run();
    void init();
    void render();
};

} // namespace engine

#endif // !ENGINE_STAGE_H_
