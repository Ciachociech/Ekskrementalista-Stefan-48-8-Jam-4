#include "engine/Instance.h"

#include <SDL_image.h>
#include <SDL_mixer.h>

namespace engine {

bool Instance::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    this->window_ =
        SDL_CreateWindow(this->instanceNameEN_.c_str(), SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH_, SCREEN_HEIGHT_, SDL_WINDOW_SHOWN);
    if (this->window_ == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    this->windowRenderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED);
    if (this->windowRenderer_ == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(this->windowRenderer_, 255, 255, 255, 255);
    managers::RenderableManager& renderableManager = managers::RenderableManager::instance(this->windowRenderer_);

    this->windowSurface_ = SDL_GetWindowSurface(this->window_);
    if (this->windowSurface_ == NULL) {
        printf("Window surface could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

bool Instance::loadMedia() {
    bool success = true;

    SDL_Surface* surface = IMG_Load(this->logoPath_.c_str());
    if (surface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", this->logoPath_.c_str(), SDL_GetError());
        return false;
    }
    SDL_SetWindowIcon(this->window_, surface);
    SDL_FreeSurface(surface);

    this->font_ = TTF_OpenFont("assets/fonts/NerkoOne-Regular.ttf", 32);
    if (this->font_ == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    Mix_Volume(-1, 64);
    /*
    if (!audioManager.init()) {
    printf("Failed to load at least one wav file! SDL_mixer Error: %s\n", Mix_GetError());
    return false;
    }
    */
    // SDL_SetWindowTitle(this->window_, this->instanceNamePL_.c_str());

    return true;
}

void Instance::close() {
    SDL_DestroyRenderer(this->windowRenderer_);
    this->windowRenderer_ = NULL;
    SDL_DestroyWindow(this->window_);
    this->window_ = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool Instance::loop() {
    bool quit = false;
    std::uint32_t frameTime;

    while (!quit) {
        frameTime = SDL_GetTicks();

        if (stage.run() == -1) { quit = true; }

        render();

        if ((SDL_GetTicks() - frameTime) < (1000.f / FPS)) {
            SDL_Delay((1000.f / FPS) - (SDL_GetTicks() - frameTime));
        }
    }

    return true;
}

void Instance::render() {
    SDL_RenderClear(this->windowRenderer_);

    stage.render();

    SDL_RenderPresent(this->windowRenderer_);
}

Instance::Instance() {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) { printf("Failed to load media!\n"); }
    }
}

Instance::~Instance() {}

void Instance::run() {
    stage.loadRenderer(this->windowRenderer_);
    stage.init();

    if (!loop()) { printf("Problem occured during running instance!"); }
    close();
}

} // namespace engine
