#ifndef ENGINE_STAGE_H_
#define ENGINE_STAGE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>

#include "input/InputKeyboard.h"
#include "managers/RenderableManager.h"
#include "Player.h"
#include "Text.h"

namespace engine {

enum class Language { ENGLISH, POLISH };

namespace {

constexpr float playerMovement = 2.5f;

}

class Stage {
private:
    // Global SDL values
    SDL_Renderer* windowRenderer_ = NULL;
    TTF_Font* font_ = NULL;
    Language* lang_ = NULL;

    // Others
    std::shared_ptr<Player> player_;
    input::InputKeyboard keyboard;
    void renderText();
    void renderHearts();
    void waitToStart();
    bool isWaitingToStart = true;
	
	//Critical fix
    std::shared_ptr<Text> lifeText;
    std::shared_ptr<Text> powerText1;
    std::shared_ptr<Text> powerText2;
    std::shared_ptr<Text> scoreText1;
    std::shared_ptr<Text> scoreText2;
    std::shared_ptr<Text> tipText1;
    std::shared_ptr<Text> tipText2;
    std::shared_ptr<Text> tipText3;
    std::shared_ptr<Text> anyKeyTest;
    std::vector<std::shared_ptr<Renderable>> hearts;
public:
    Stage();
    virtual ~Stage();

    // loading pointers to instance managers and objects
    void loadRenderer(SDL_Renderer* renderer);
    void loadFont(TTF_Font* font);
    void loadLanguage(Language* lang);

    // Game functions
    std::int8_t run();
    void init();
    void render();
};

} // namespace engine

#endif // !ENGINE_STAGE_H_
