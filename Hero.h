#ifndef HERO__H_
#define HERO__H_

#include <SDL.h>
#include <SDL_image.h>

class Hero {
public:
    int x, y;
    SDL_Texture* texture;
    SDL_Rect rect;
    int stepX = 0;
    int stepY = 0;

    Hero(int _x, int _y, SDL_Texture* _texture, double scale) :texture(_texture) {
        rect.x = _x;
        rect.y = _y;
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
        rect.w *= scale;
        rect.h *= scale;
    };

    void render(SDL_Renderer* renderer) {
        SDL_RenderCopy( renderer, texture, NULL, &rect );
    }

    void setDirection(int _stepX, int _stepY) {
        stepX = _stepX;
        stepY = _stepY;
    }

    void move() {
        rect.x += stepX;
        rect.y += stepY;
    }

    bool outside(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
        return rect.x < 0 || rect.y < 0 || rect.x > SCREEN_WIDTH || rect.y > SCREEN_HEIGHT;
    }
};

#endif
