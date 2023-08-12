#include "engine/Renderable.h"

#include <SDL_image.h>

namespace engine {

Renderable::Renderable()
    : x_(0), y_(0), w_(0), h_(0), scaleX_(1.f), scaleY_(1.f), frames_(1), sides_(1),
      currentFrame_(0), texture_(NULL), spriteSide_(lookAt::left) {}

Renderable::Renderable(float x, float y)
    : x_(x), y_(y), w_(0), h_(0), scaleX_(1.f), scaleY_(1.f), frames_(1), sides_(1),
      currentFrame_(0), texture_(NULL), spriteSide_(lookAt::left) {}

Renderable::~Renderable() {}

bool Renderable::loadFromFile(float scaleX, float scaleY, int frames, int sides,
                              std::uint16_t animationTime, std::string filepath,
                              SDL_Renderer* renderer) {
    free();

    SDL_Texture* texture = NULL;

    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(),
               SDL_GetError());
        return false;
    }

    this->w_ = surface->w / frames;
    this->h_ = surface->h / sides;
    this->scaleX_ = scaleX;
    this->scaleY_ = scaleY;
    this->frames_ = frames;
    this->sides_ = sides;
    this->animationTime_ = animationTime;

    SDL_FreeSurface(surface);

    this->firstInit_ = false;
    this->currentFrame_ = this->frames_ - 1;
    this->texture_ = texture;
    return this->texture_ != NULL;
}

void Renderable::free() {
    if (this->texture_ != NULL) {
        SDL_DestroyTexture(this->texture_);
        this->texture_ = NULL;
        this->w_ = 0;
        this->h_ = 0;
    }
}

void Renderable::render(int x, int y, SDL_Renderer* renderer) {
    ++this->currentFrame_ %= this->frames_;
    SDL_Rect srcRenderQuad = {(this->currentFrame_ / (this->animationTime_ / this->frames_)) *
                                  this->w_,
                              (int)(this->spriteSide_) * this->h_, this->w_, this->h_};
    SDL_Rect dstRenderQuad = {this->x_ + x, this->y_ + y, this->scaleX_ * this->w_,
                              this->scaleY_ * this->h_};
    SDL_RenderCopy(renderer, this->texture_, &srcRenderQuad, &dstRenderQuad);
}

void Renderable::update(float x, float y) {
    this->x_ += x;
    this->y_ += y;
    this->bulletFrameCounter_++;
}

void Renderable::setSpriteSide(lookAt newSide) { this->spriteSide_ = newSide; }

float Renderable::X() { return this->x_; }

float Renderable::Y() { return this->y_; }

std::uint16_t Renderable::W() { return this->w_; }

std::uint16_t Renderable::H() { return this->h_; }

std::uint32_t Renderable::getBulletFrameCounter() { return this->bulletFrameCounter_; }

void Renderable::resetBulletFrameCounter() { this->bulletFrameCounter_ = 0; }

} // namespace engine
