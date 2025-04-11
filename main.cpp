#include <SDL.h>
#include "graphics.h"
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
vector<vatcan> b;

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
	graphics.prepareScene();
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("img\\nen.jpg"));
    SDL_Texture* coc = graphics.loadTexture("img\\coc.png");
    SDL_Texture* chim[2];
    chim[0] = graphics.loadTexture("animation\\chim1.png");
	chim[1] = graphics.loadTexture("animation\\chim2.png"); 
    bool quit = false;
    int v = 1;
    int time = 0;
    SDL_Event e;
    SDL_Texture* character[7];
	SDL_Texture* cui[7];
	SDL_Texture* thuacui = graphics.loadTexture("animation/thua1.png");
    character[0] = graphics.loadTexture("animation/go1.png");
    character[1] = graphics.loadTexture("animation/go2.png");
    character[2] = graphics.loadTexture("animation/go3.png");
    character[3] = graphics.loadTexture("animation/go4.png");
    character[4] = graphics.loadTexture("animation/go5.png");
    character[5] = graphics.loadTexture("animation/go6.png");
    character[6] = graphics.loadTexture("animation/go7.png");
	cui[0] = graphics.loadTexture("animation/cui1.png");
	cui[1] = graphics.loadTexture("animation/cui2.png");
	cui[2] = graphics.loadTexture("animation/cui3.png");
	cui[3] = graphics.loadTexture("animation/cui4.png");
	cui[4] = graphics.loadTexture("animation/cui5.png");
	cui[5] = graphics.loadTexture("animation/cui6.png");
	cui[6] = graphics.loadTexture("animation/cui7.png");

	//chua thua
	SDL_Texture* thuadung = graphics.loadTexture("animation/thua.png");
    //man hinh thua
	TTF_Init();
	TTF_Font* font_gameover = loadFont("orange juice 2.0.ttf", 60);
    SDL_Texture* gameover = renderText("Game Over", font_gameover, { 0, 0, 0 }, graphics.renderer);
    //Score
	TTF_Font* font_score = loadFont("orange juice 2.0.ttf", 20);
    int Y = 254, base = 15, yV;
    //nut resert
	SDL_Texture* reset = graphics.loadTexture("img\\reset.png");
	//am thanh
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Chunk* am_thanh_thua = loadSound("sound\\die.mp3");
    Mix_Chunk* nhay = loadSound("sound\\jump.mp3");
	Mix_Chunk* point = loadSound("sound\\point.mp3");
	Mix_Music* nhacnen = loadMusic("sound\\nhac.mp3");
    //game chay
    while (!quit) {
        int score = time/5;
		
        int kq = max(kq,score);
        play(nhacnen);
        time++;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
				graphics.thoat();
            }

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
		string s3 = "High Score: ";
		string s4 = to_string(kq);
		string tong = s3 + s4;
		char const* kiluc = tong.c_str();
        SDL_Texture* Score = renderText(s, font_score, {0, 0, 0}, graphics.renderer);
		SDL_Texture* High = renderText(kiluc, font_score, { 0, 0, 0 }, graphics.renderer);
		if (score % 100 == 0 && score != 0) {
			play(point);
		}
        if (score > kq) {
			play(point);
        }
        graphics.renderTexture(Score, 0, 0);
        
        graphics.renderTexture(High, 0, 20);
        
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
            play(nhay);
        }
        if (key[SDL_SCANCODE_DOWN]) {
            if (Y == 254) {
                graphics.renderTexture(cui[(time / 5) % 7], 0, Y);

                yV = base;
                Y += yV;
            }
            else {
                graphics.renderTexture(character[(time / 5) % 7], 0, Y);
            }
        }
        
        
    
        //graphics.renderTexture(chim, 73, 240);
        //SDL_Rect r = { 73, 240, 31, 30 };
        //SDL_RenderDrawRect(graphics.renderer, &r);

        if (time % 100 == 0 && v < 75) {
            v++;
        }
        //xu li va cham
        for (auto& i : b) {

            if (i.type == 1) {
                i.hitbox.x -= v;
                graphics.renderTexture(coc, i.hitbox.x - 23, i.hitbox.y - 25);
            }
            else {
                i.hitbox.x -= v;
                graphics.renderTexture(chim[(time%50) > 24], i.hitbox.x, i.hitbox.y);
            }
		
            if (check(nv_dung, i.hitbox) && !key[SDL_SCANCODE_DOWN]) {
                quit = true;
            }
            if (check(nv_cui, i.hitbox) && key[SDL_SCANCODE_DOWN]) {

                quit = true;
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
				tmp.hitbox.y = 240;
				tmp.hitbox.w = 31;
				tmp.hitbox.h = 30;
			}
          
            b.push_back(tmp);
        }
        if (rd() % 100 == 0 && b.size() && b.back().hitbox.x <= 650) {
            vatcan tmp;
            tmp.type = rd() % 2;
			if (tmp.type == 1) {
				tmp.hitbox.x = 800;
				tmp.hitbox.y = 270;
				tmp.hitbox.w = 15;
				tmp.hitbox.h = 43;b.push_back(tmp);
			}
            else {
				tmp.hitbox.x = 800;
				tmp.hitbox.y = 240;
				tmp.hitbox.w = 31;
				tmp.hitbox.h = 30;b.push_back(tmp);
			}
            

        }

        graphics.presentScene();
       
       
        //thua
        
        int cnt = 0;
        if (quit == false) {
            cnt = 0;
            
        }

        while (quit) {
            Mix_ResumeMusic();
            SDL_RenderClear(graphics.renderer);
			graphics.renderTexture(background.texture, 0, 0);
            graphics.renderTexture(gameover, 258, 40);
            graphics.renderTexture(Score, 0, 0);
            
			if(cnt ==0){
				play(am_thanh_thua);
                cnt++;
            }
			
            for (auto& i : b) {
                if (i.type == 1) {
                    graphics.renderTexture(coc, i.hitbox.x - 23, i.hitbox.y - 25);

				}
                else {
                    graphics.renderTexture(chim[time%50>24], i.hitbox.x-15, i.hitbox.y-20);
                }
                
            }
            
			graphics.renderTexture(reset, 350, 250);
			
            int x, y;
            SDL_Rect res;
			res.x = 350; res.y = 250;
			res.w = 100; res.h = 100;
            SDL_PollEvent(&e);
            SDL_GetMouseState(&x, &y);

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Rect mouse;
                mouse.x = x; mouse.y = y;
                mouse.h = 0; mouse.w = 0;
                if (check(mouse, res)) {
					time = 0;
                    v = 1;
					Y = 254;
					quit = false;
					b.clear();
                }
            }
            if (e.type == SDL_QUIT) {
				graphics.thoat();
            }
			graphics.presentScene();
			SDL_RenderPresent(graphics.renderer);
			SDL_Delay(10);
        }
        
}
if (b.size() && b[0].hitbox.x <= 0) {
    b.erase(b.begin());

}
    graphics.thoat();

    return 0;
}