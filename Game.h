#ifndef GAME__H_
#define GAME__H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Hero.h"
#include "SDL_Utils.h"

enum Action {LEFT, RIGHT, UP, DOWN, NONE, QUIT, PAUSE};

class Game {
public:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const char* WINDOW_TITLE = "Texture Test";

    const char* backgroundImagePath = "bikiniBottom.jpg";
    const char* spongeBobImagePath = "Spongebob.png";
    const char* gameOverImagePath = "balloons.png";
    const SDL_Color BGR_COLOR = {255, 255, 255};

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* backgroundTxt;
    SDL_Texture* spongeBobTxt;
    SDL_Texture* gameOverTxt;

    vector<Hero*> heros;

    void init() {
        initSDL(window, renderer, WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

        backgroundTxt = loadTexture(backgroundImagePath, renderer);
        spongeBobTxt = loadTexture(spongeBobImagePath, renderer);
        gameOverTxt = loadTexture(gameOverImagePath, renderer);

        addSpongeBob();
    }

    void clearScreen() {
        SDL_SetRenderDrawColor(renderer, BGR_COLOR.r, BGR_COLOR.g, BGR_COLOR.b, 0);
        SDL_RenderClear(renderer);
    }

    void addSpongeBob() {
        Hero* h = new Hero(100, 100, spongeBobTxt, .5);
        h->setDirection(2,2);
        heros.push_back(h);
    }

    bool over() {
        return heros.empty();
    }

    void render() {
        clearScreen();
        SDL_RenderCopy( renderer, backgroundTxt, NULL, NULL);

        for (Hero* h: heros) h->render(renderer);

        SDL_RenderPresent( renderer );
    }

    void renderGameOver() {
        clearScreen();
        SDL_RenderCopy( renderer, backgroundTxt, NULL, NULL);
        SDL_RenderCopy( renderer, gameOverTxt, NULL, NULL);
        SDL_RenderPresent( renderer );
    }

    void destroy() {
        for (Hero* h: heros) { delete h; }
        SDL_DestroyTexture( spongeBobTxt );
        SDL_DestroyTexture( backgroundTxt );
        SDL_DestroyTexture( gameOverTxt );

        quitSDL(window, renderer);
    }

    void move(Action action) {
        if (action != NONE) addSpongeBob();

        for (vector<Hero*>::iterator it = heros.begin();
                it != heros.end(); )
        {
            Hero * h = *it;
            h->move();

            if (h->outside(SCREEN_WIDTH, SCREEN_HEIGHT)) {
                it = heros.erase(it);
                delete h;
            }
            else ++it;
        }
    }
};

#endif
