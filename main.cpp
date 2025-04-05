#include <SDL.h>
#include "graphics.h"
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

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
int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
	graphics.prepareScene();
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("img\\nen.jpg"));
    SDL_Texture* coc = graphics.loadTexture("img\\coc.png");
    SDL_Texture* chim = graphics.loadTexture("img\\fly.png");
    vector<vatcan> b;
    bool quit = false;
    int v = 1;
    int time = 0;
    SDL_Event e;
    SDL_Texture* character[9];
	SDL_Texture* thua = graphics.loadTexture("animation/thua1.png");
    character[0] = graphics.loadTexture("animation/go1.png");
    character[1] = graphics.loadTexture("animation/go2.png");
    character[2] = graphics.loadTexture("animation/go3.png");
    character[3] = graphics.loadTexture("animation/go4.png");
    character[4] = graphics.loadTexture("animation/go5.png");
    character[5] = graphics.loadTexture("animation/go6.png");
    character[6] = graphics.loadTexture("animation/go7.png");
	character[7] = graphics.loadTexture("animation/cui.png");
	character[8] = graphics.loadTexture("animation/thua.png");
    //man hinh thua
	TTF_Init();
	TTF_Font* font_gameover = loadFont("orange juice 2.0.ttf", 60);
    SDL_Texture* gameover = renderText("Game Over", font_gameover, { 0, 0, 0 }, graphics.renderer);
    //Score
	TTF_Font* font_score = loadFont("orange juice 2.0.ttf", 20);
    int Y = 254, base = 15, yV;
    
	
    //game chay
    while (!quit) {
        int score = time;

        time++;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;

        }
        background.scroll(v);
        graphics.render(background);
        
        SDL_Rect nv_dung = { 0, Y + 8, 64, 46 };
		
        SDL_Rect nv_cui = {0,Y+3,60,35};
        // tạo bảng điểm
		string s1 = "Score: ";
		string s2 = to_string(score);
        string a = s1 + s2;
		char const *s = a.c_str();
        SDL_Texture* Score = renderText(s, font_score, {0, 0, 0}, graphics.renderer);
        graphics.renderTexture(Score, 0, 0);
        const Uint8* key = SDL_GetKeyboardState(NULL);
        while(!key[SDL_SCANCODE_DOWN]){ 
            graphics.renderTexture(character[(time / 5) % 7], 0, Y);
            break;
        }
        if (Y - 254) {
            Y -= --yV;
            Y = min(Y, 254);
        }

        if (Y == 254 && key[SDL_SCANCODE_SPACE]) {
            yV = base;
            Y -= yV;
        }
        if (key[SDL_SCANCODE_DOWN]) {
            if (Y == 254) {
                graphics.renderTexture(character[7], 0, Y);

                yV = base;
                Y += yV;
            }
            else {
                graphics.renderTexture(character[(time / 5) % 7], 0, Y);
            }
        }
        
        
    
        //graphics.renderTexture(chim, 73, 245);
        //SDL_Rect r = { 73, 245, 25, 30 };
        //SDL_RenderDrawRect(graphics.renderer, &r);

        if (time % 100 == 0 && v < 75) {
            v++;
        }
        for (auto& i : b) {
            if (i.type == 1) {
                i.hitbox.x -= v;
                graphics.renderTexture(coc, i.hitbox.x - 23, i.hitbox.y - 25);
            }
            else {
                i.hitbox.x -= v;
                graphics.renderTexture(chim, i.hitbox.x - 50, i.hitbox.y - 50);
            }
        }

        if (rd() % 100 == 0 && b.size() == 0) {
            vatcan tmp;
			tmp.type = rd() % 2;
            if (tmp.type == 1) {
                tmp.hitbox.x = 800;
                tmp.hitbox.y = 270;
                tmp.hitbox.w = 15;
                tmp.hitbox.h = 43;
			}
			else {
				tmp.hitbox.x = 800;
				tmp.hitbox.y = 270;
				tmp.hitbox.w = 50;
				tmp.hitbox.h = 50;
			}
          
            b.push_back(tmp);
        }
        if (rd() % 100 == 0 && b.size() && b.back().hitbox.x <= 700) {
            vatcan tmp;
            tmp.type = rd() % 2;
			if (tmp.type == 1) {
				tmp.hitbox.x = 800;
				tmp.hitbox.y = 270;
				tmp.hitbox.w = 15;
				tmp.hitbox.h = 43;
			}
			else {
				tmp.hitbox.x = 800;
				tmp.hitbox.y = 270;
				tmp.hitbox.w = 50;
				tmp.hitbox.h = 50;
			}
            
            b.push_back(tmp);

        }

        graphics.presentScene();
        // xử lí va chạm
        for (auto& i : b) {
            if (check(nv_dung, i.hitbox)&& !key[SDL_SCANCODE_DOWN]) {

                cerr << "Game Over" << endl;
                quit = true;
            }
            if (check(nv_cui, i.hitbox) && key[SDL_SCANCODE_DOWN]) {
                
                cerr << "Game Over" << endl;
               
                quit = true;
            }
          
        }
        
        if (b.size() && b[0].hitbox.x <= 0) {
            b.erase(b.begin());

        }
        //thua
        if (quit) {
			
            SDL_RenderClear(graphics.renderer);
			graphics.renderTexture(background.texture, 0, 0);
            graphics.renderTexture(gameover, 258, 40);
            graphics.renderTexture(Score, 0, 0);
            for (auto& i : b) {
                if (i.type == 1) {
                    graphics.renderTexture(coc, i.hitbox.x - 23, i.hitbox.y - 25);

                }
                
            }
            if (key[SDL_SCANCODE_DOWN]) {
				graphics.renderTexture(thua, 0, Y-yV);
            }
            else {
                graphics.renderTexture(character[8], 0, Y);
            }
			SDL_RenderPresent(graphics.renderer);
			SDL_Delay(10);
        }
        
        SDL_RenderClear(graphics.renderer);
        SDL_Delay(10);
		
        
}
	waitUntilKeyPressed();
    
    graphics.thoat();

    return 0;
}