
#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <vector>
#include <string>
#include <random>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;
bool inmenu = true;
bool quit = false;
int v = 1, vtmp = 1;
int score = 0;
int volume = 60;
bool playGame = false;
bool playMenu = true;
bool flag = 0, flag2 = 0;
int Y = 254, base = 15, yV;


mt19937 rd(time(NULL));
struct hieuung {
	SDL_Texture* texture;
	int x, y;
	
	int time;
};
SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer) {
    SDL_Surface* textSurface =
        TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == nullptr) return nullptr;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
    return texture;
}
TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* gFont = TTF_OpenFont(path, size);

    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }

    return gFont;
}
void play(Mix_Music* gMusic) {
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    }

    else if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    }
}
void play(Mix_Chunk* gChunk) {
	if (gChunk != nullptr) {
		Mix_PlayChannel(-1, gChunk, 0);
	}
}
Mix_Chunk* loadSound(const char* path) {
	Mix_Chunk* gChunk = Mix_LoadWAV(path);
	
	return gChunk;
}
Mix_Music* loadMusic(const char* path) {
	Mix_Music* gMusic = Mix_LoadMUS(path);
	return gMusic;
}
struct vatcan {
    SDL_Rect hitbox[2];
    int type;
	
};
struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if (scrollingOffset < 0) { scrollingOffset = width; }
    }
};


struct Graphics {
    SDL_Renderer* renderer;
    SDL_Window* window;
    void render(const ScrollingBackground& bgr) {
        renderTexture(bgr.texture, bgr.scrollingOffset, 0);
        renderTexture(bgr.texture, bgr.scrollingOffset - bgr.width, 0);
    }
    void waitUntilKeyPressed()
    {
        SDL_Event e;
        while (true) {
            if (SDL_PollEvent(&e) != 0 &&
                (e.type == SDL_QUIT))
                return;
            SDL_Delay(100);
        }
    }
    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
            "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
        if (window == nullptr)
            logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit("SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
            logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void thoat() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit;
   }
	SDL_Texture* loadTexture(const char* filename) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
		SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
		if (texture == NULL)
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
		return texture;

    }
    void prepareScene(SDL_Texture* background = nullptr)
    {
        SDL_RenderClear(renderer);
        if (background != nullptr) SDL_RenderCopy(renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }
  
    

    void renderTexture(SDL_Texture* texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
   
};
bool check(SDL_Rect &a, SDL_Rect &b) {
	if (a.x + a.w < b.x) return false;
	if (a.x > b.x + b.w) return false;
	if (a.y + a.h < b.y) return false;
	if (a.y > b.y + b.h) return false;
	return true;
}
bool check1(SDL_Rect a[], SDL_Rect b[]) {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0;j < 2;j++) {
            if (check(a[i], b[j])) {
                return true;
            }
        }
    }
	return false;
}

#endif // _GRAPHICS__H
