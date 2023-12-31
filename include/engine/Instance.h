#ifndef ENGINE_INSTANCE_H_
#define ENGINE_INSTANCE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <cstdint>
#include <string>

#include "Stage.h"

namespace engine {

class Instance {
private:
    // Screen resolution
    const std::uint16_t SCREEN_WIDTH_ = 1200;
    const std::uint16_t SCREEN_HEIGHT_ = 800;

    // Global SDL values
    SDL_Window* window_ = NULL;
    SDL_Surface* windowSurface_ = NULL;
    SDL_Renderer* windowRenderer_ = NULL;
    TTF_Font* font_ = NULL;

    // Global SDL values
    const int FPS = 60;
    const std::string logoPath_ = "assets/icons/game.png";
    const std::string gameVersion_ = "0.2.10";
    const std::string instanceNamePL_ = u8"Ekskrementalista Stefan (Skrócona wersja z Kretk¹ - " + gameVersion_ + ")";
    const std::string instanceNameEN_ = u8"Stefan the Excrementalist (Kretka's Reduced Version - " + gameVersion_ + ")";

    // Game managers

    // Functions
    bool init();
    bool loadMedia();
    void close();
    bool loop();
    void render();

    // Others
    Stage stage;
    Language lang_;
public:
    Instance();
    virtual ~Instance();

    void run();
};

} // namespace engine

#endif // !ENGINE_INSTANCE_H_
