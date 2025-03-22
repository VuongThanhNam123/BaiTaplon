/*
 * A simple stupid game that is a good start to build any games in a clean and simple way.

 * Rule: a game is over when there is no SpongeBob left.
 * How to play: Use arrow keys to add more SpongeBob.
 */
#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include "SDL_Utils.h"
#include "Game.h"

using namespace std;

Action getUserAction();

void showMenu(SDL_Renderer*);
SDL_Point getMouseAction();

int main(int argc, char* argv[])
{
    srand(time(0));
    Game game;
    game.init();

    bool paused = false;

    showMenu(game.renderer);
    game.render();
    do {
        Action action = getUserAction();
        if (action == QUIT) break;
        if (action == PAUSE) {
            paused = !paused;
        }
        if (paused) continue;

        game.move(action);
        game.render();
        SDL_Delay(10);
    } while (!game.over());
    game.renderGameOver();

    waitUntilKeyPressed();

    game.destroy();
    return 0;
}

void showMenu(SDL_Renderer* renderer) {
    SDL_Rect filled_rect;
    filled_rect.x = 100;
    filled_rect.y = 100;
    filled_rect.w = 10;
    filled_rect.h = 10;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
}

SDL_Point getMouseAction() {
    SDL_Event e;
    int mouseX;
    int mouseY;
    SDL_Point mouse;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_MOUSEMOTION:
            mouse.x = e.motion.x;
            mouse.y = e.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) return mouse;
        }
    }
}

Action getUserAction() {
    SDL_Event e;
    if (SDL_PollEvent(&e) == 0) return NONE;
    if (e.type == SDL_QUIT) return QUIT;
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_ESCAPE: return QUIT;
        case SDLK_LEFT: return LEFT;
        case SDLK_RIGHT: return RIGHT;
        case SDLK_DOWN: return DOWN;
        case SDLK_UP: return UP;
        case SDLK_PAUSE: return PAUSE;
        default: return NONE;
        }
    }
    return NONE;
}