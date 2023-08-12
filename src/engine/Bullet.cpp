#include "engine/Bullet.h"

namespace engine {
	
Bullet::Bullet(float x, float y, bool isHostile, std::function<void(float& x, float& y)> movementPattern) : Renderable(x, y), Collisionable(isHostile ? CollisionEntityType::ENEMY_BULLET : CollisionEntityType::ALLY_BULLET), movementPattern_(movementPattern) {
    this->setCenter(x + (W() / 2), y + (H() / 2));
    this->setRadius(H() / 2);
}

Bullet::~Bullet() {}

void Bullet::update(float x, float y) {
	float movX = 0;
	float movY = 0;

	this->movementPattern_(movX, movY);
	Renderable::update(movX, movY);
    this->setCenter(X() + W() / 2 + movX, Y() + H() / 2 + movY);
}

void Bullet::render(int cameraX, int cameraY, SDL_Renderer* renderer) {
	Renderable::render(cameraX, cameraY, renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    const float diameter = (R() * 2);

    int32_t x = (R() - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centerX() + x, centerY() - y);
        SDL_RenderDrawPoint(renderer, centerX() + x, centerY() + y);
        SDL_RenderDrawPoint(renderer, centerX() - x, centerY() - y);
        SDL_RenderDrawPoint(renderer, centerX() - x, centerY() + y);
        SDL_RenderDrawPoint(renderer, centerX() + y, centerY() - x);
        SDL_RenderDrawPoint(renderer, centerX() + y, centerY() + x);
        SDL_RenderDrawPoint(renderer, centerX() - y, centerY() - x);
        SDL_RenderDrawPoint(renderer, centerX() - y, centerY() + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

}