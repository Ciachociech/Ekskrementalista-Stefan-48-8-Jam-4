#ifndef ENGINE_RENDERABLE_H_
#define ENGINE_RENDERABLE_H_

#include <cstdint>
#include <string>

#include <SDL.h>

namespace engine {

enum class lookAt {
    none = -1,
    left = 0,
    right,
    up,
    down
};

class Renderable {
private:
    // Global SDL values
    SDL_Texture* texture_;

    // Other values
    float x_;
    float y_;
    std::uint16_t w_;
    std::uint16_t h_;
    float scaleX_;
    float scaleY_;
    std::uint16_t frames_;
    std::uint16_t sides_;
    std::uint16_t animationTime_;
    std::uint16_t currentFrame_ = 0;
    lookAt spriteSide_;
    bool firstInit_ = true;

public:
    Renderable();
    Renderable(float x, float y);
    virtual ~Renderable();

    virtual bool loadFromFile(float scaleX, float scaleY, int frames, int sides,
                              std::uint16_t animationTime_, std::string filepath,
                              SDL_Renderer* renderer);
    void free();
    virtual void render(int cameraX, int cameraY, SDL_Renderer* renderer);

    virtual void move(float x, float y);
    void setSpriteSide(lookAt newSide);

    float X();
    float Y();
    std::uint16_t W();
    std::uint16_t H();
};

} // namespace engine

#endif // !ENGINE_RENDERABLE_H_
