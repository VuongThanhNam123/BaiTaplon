#include <SDL.h>
#include "graphics.h"
#include "defs.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream> 
using namespace std;

int main(int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
    graphics.prepareScene();
    ScrollingBackground background;
    vector<vatcan> b;
    vector<hieuung> hieu_ung;
    SDL_Rect nv[4];
    SDL_Rect chim_hitbox[2];
    background.setTexture(graphics.loadTexture("img\\nen.jpg"));
    SDL_Texture* coc = graphics.loadTexture("img\\coc.png");
    SDL_Texture* chim[2];
    SDL_Texture* hopqua = graphics.loadTexture("img\\hopqua.png");
    chim[0] = graphics.loadTexture("animation\\chim1.png");
    chim[1] = graphics.loadTexture("animation\\chim2.png");
   
    SDL_Event e;
    SDL_Texture* character[7];
    SDL_Texture* cui[7];
    SDL_Texture* menuBackground = graphics.loadTexture("img\\menu.png");
    for (int i = 0;i < 7;i++) {
		string s = "animation/go" + to_string(i + 1) + ".png";
        character[i] = graphics.loadTexture(s.c_str());
    }
	for (int i = 0;i < 7;i++)
	{
		string s = "animation/cui" + to_string(i + 1) + ".png";
		cui[i] = graphics.loadTexture(s.c_str());
	}
    
    int time = 0;
    //chua thua
    SDL_Texture* thuadung = graphics.loadTexture("animation/thua.png");
    //man hinh thua
    TTF_Init();
    TTF_Font* font_thuong = loadFont("CommodorePixeled.ttf", 25);
    TTF_Font* font_gameover = loadFont("CommodorePixeled.ttf", 50);

    SDL_Texture* gameover = renderText("Game Over", font_gameover, { 0, 0, 0 }, graphics.renderer);
    SDL_Texture* thuongdiem = renderText("+50", font_thuong, { 15, 76, 129 }, graphics.renderer);
    SDL_Texture* settingmenu = graphics.loadTexture("img\\setting.jpg");
    //Score
    TTF_Font* font_score = loadFont("CommodorePixeled.ttf", 13);
    
    //nut resert
    SDL_Texture* reset = graphics.loadTexture("img\\reset.png");
    //am thanh
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk* am_thanh_thua = loadSound("sound\\die.mp3");
    Mix_Chunk* nhay = loadSound("sound\\jump.mp3");
    Mix_Chunk* point = loadSound("sound\\point.mp3");
    Mix_Music* nhacnen = loadMusic("sound\\nhac.mp3");
    Mix_Chunk* thuong = loadSound("sound\\thuong.mp3");
    
    Mix_VolumeMusic(volume);
    //menu
    
    //game chay
    while (!quit) {


        while (!quit && !playGame) {
            SDL_Event e;
                    u:;
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    graphics.thoat();
                }

                if (e.button.button == SDL_SCANCODE_SPACE) {
                    playGame = true;
                }

                SDL_RenderCopy(graphics.renderer, menuBackground, NULL, NULL);

                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Rect start = { 225, 230, 360, 78 };
                        SDL_RenderCopy(graphics.renderer, menuBackground, NULL, NULL);
                        
                        

                SDL_Rect setting = { 225, 340, 360, 76 };

                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    SDL_Rect mouse;
                    mouse.x = x; mouse.y = y;
                    mouse.h = 0; mouse.w = 0;
                    if (check(mouse, start)) {
                        playGame = true;
                    }
                    if (check(mouse, setting)) {
                        bool flag = 0, flag2 = 0;
                        playMenu = true;
                        graphics.prepareScene();
                        while (playMenu) {
                            SDL_Rect return_rect = { 230, 450, 330, 90 };
                            SDL_Rect sliderBar = { 250 + 100, 200 - 25, 300, 10 };
                            SDL_Rect sliderKnob = { 250 + 100 + (volume * 300 / 128) - 5, 195 - 25, 10, 20 };
                            SDL_Rect sliderBar2 = { 250 + 100, 200 - 25 + 90, 300, 10 };
                            SDL_Rect sliderKnob2 = { 250 + 100 + (v * 300 / 128) - 5, 195 - 25 + 90, 10, 20 };
                            
                            while (1) {
                                while (SDL_PollEvent(&e)) {


                                    if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION) {
                                        if (e.button.button == SDL_BUTTON_LEFT) {
                                            int dx = e.button.x, dy = e.button.y;
                                            if ((flag || (dy >= sliderBar.y - 10 && dy <= sliderBar.y + sliderBar.h + 10))
                                                && dx >= sliderBar.x && dx <= sliderBar.x + sliderBar.w && !flag2) {
                                                volume = (dx - sliderBar.x) * 128 / sliderBar.w;
                                                Mix_VolumeMusic(volume); Mix_Volume(-1, volume);
                                                sliderKnob.x = dx - 5; flag = 1;
                                            }

                                            if ((flag2 || (dy >= sliderBar2.y - 10 && dy <= sliderBar2.y + sliderBar2.h + 10))
                                                && dx >= sliderBar2.x && dx <= sliderBar2.x + sliderBar2.w && !flag) {
                                                v = vtmp = (dx - sliderBar2.x) * 128 / sliderBar2.w;
                                                sliderKnob2.x = dx - 5; flag2 = 1;
                                            }
                                        }
                                    }

                                    if (e.type == SDL_MOUSEBUTTONUP) flag2 = 0, flag = 0;
                                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                                        SDL_GetMouseState(&x, &y);
                                        SDL_Rect mouse = { x, y, 0, 0 };

                                        if (check(mouse, return_rect)) {
                                            SDL_RenderClear(graphics.renderer);
                                            playMenu = 0;
                                            goto u;
                                        }
                                    }

                                }
                                SDL_SetRenderDrawColor(graphics.renderer, 150, 150, 150, 255);
                                SDL_RenderCopy(graphics.renderer, settingmenu, NULL, NULL);
                                SDL_RenderFillRect(graphics.renderer, &sliderBar2);
                                SDL_RenderFillRect(graphics.renderer, &sliderBar);
                                SDL_SetRenderDrawColor(graphics.renderer, 200, 150, 150, 255);
                                SDL_RenderFillRect(graphics.renderer, &sliderKnob2);
                                SDL_RenderFillRect(graphics.renderer, &sliderKnob);
                            
                                SDL_RenderPresent(graphics.renderer);
                                SDL_RenderClear(graphics.renderer);
                            }

                        }

                    }
                }

                SDL_RenderPresent(graphics.renderer);
            }



        }
        if (time % 5 == 0) {
            score++;
           
        }
        

        int kq = max(kq, score);
        play(nhacnen);
        time++;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                graphics.thoat();
            }

        }
        background.scroll(v);
        graphics.render(background);
        vector<hieuung> tmp;
        for (auto& i : hieu_ung) {
            Uint8 fade = (Uint8)(260.0f * i.time / 20.0f);
            SDL_SetTextureAlphaMod(i.texture, fade);
            graphics.renderTexture(i.texture, i.x, i.y);
            i.time--;
            if (i.time) {
                tmp.push_back(i);
            }
        }
        hieu_ung = tmp;
        Mix_ResumeMusic();

        // tạo bảng điểm
        string s1 = "Score:";
        string s2 = to_string(score);
        string a = s1 + s2;
        char const* s = a.c_str();
        string s3 = "High Score:";
        string s4 = to_string(kq);



        string tong = s3 + s4;
        char const* kiluc = tong.c_str();
        int x;
        ifstream fileIn("highscore.txt");
        fileIn >> x;
        if (x > kq) {
            kq = x;
        }
        fileIn.close();
        if (kq > x) {
            ofstream out("highscore.txt");
            out << x;

        }

        SDL_Texture* Score = renderText(s, font_score, { 0, 0, 0 }, graphics.renderer);
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
        bool cui1 = 0;
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
                cui1 = 1;
                yV = base;

            }

        }
        nv[0] = { 35, Y + 11,18, 18 };
        nv[1] = { 20, Y + 25, 30, 13 };
        nv[2] = { 0, Y + 29, 20, 10 };
        nv[3] = { 20, Y + 40, 20, 10 };
        if (cui1 == 1) {
            graphics.renderTexture(cui[(time) / 4 % 7], 0, Y);

            nv[0] = { 34, Y + 18, 18, 18 };
        }
        else {
            graphics.renderTexture(character[(time) / 4 % 7], 0, Y);

        }
       

        if (time % 100 == 0 && v < 75) {
            v++;
        }
        //xu li va cham

        int xoa = 0;

        for (auto& i : b) {

            if (i.type == 1) {
                i.hitbox[0].x -= v;
                i.hitbox[1].x -= v;
                graphics.renderTexture(coc, i.hitbox[0].x - 23, i.hitbox[0].y - 25);
                if (i.hitbox[0].w > 15) {
                    graphics.renderTexture(coc, i.hitbox[0].x - 8, i.hitbox[0].y - 25);
                }
                if (i.hitbox[0].w > 30) {
                    graphics.renderTexture(coc, i.hitbox[0].x + 7, i.hitbox[0].y - 25);
                }

            }
            if (i.type == 2) {
                i.hitbox[0].x -= v;
                i.hitbox[1].x -= v;

                graphics.renderTexture(chim[(time % 50) > 24], i.hitbox[0].x, i.hitbox[0].y - 11);
                if ((time % 50) > 24) {
                    i.hitbox[0].y -= 10;
                }
            }
            if (i.type == 0) {
                i.hitbox[0].x -= v;
                i.hitbox[1].x -= v;
                graphics.renderTexture(hopqua, i.hitbox[0].x - 5, i.hitbox[0].y - 5);

            }
            if (check1(nv, i.hitbox) && cui1 == 0 && i.type != 0) {

                quit = true;


            }
            if (check1(nv, i.hitbox) && cui1 == 1 && i.type != 0) {

                quit = true;
            }
            if (check1(nv, i.hitbox) && cui1 == 0 && i.type == 0) {
                score += 50;
                hieu_ung.push_back({ thuongdiem,0, 220, 20 });

                play(thuong);
                xoa++;
            }

            if (quit) {
                break;
            }
            if (check1(nv, i.hitbox) && cui1 == 1 && i.type == 0) {
                score += 50;
                hieu_ung.push_back({ thuongdiem,0, 220, 20 });
                play(thuong);
                xoa++;
            }
            if (i.type == 2) {
                if ((time % 50) > 24) {
                    i.hitbox[0].y += 10;
                }

            }
        }

        if (rd() % 40 == 0 && b.size() == 0) {
            vatcan tmp;
            tmp.type = rd() % 3;

            if (tmp.type == 1) {
                for (int t = 0; t < 2; t++) {
                    tmp.hitbox[t].y = 270;
                    tmp.hitbox[t].h = 43;
                    int x = rd() % 3;
                    if (x == 0) {
                        tmp.hitbox[t].x = 800;
                        tmp.hitbox[t].w = 15;
                    }
                    else if (x == 1) {
                        tmp.hitbox[t].x = 785;
                        tmp.hitbox[t].w = 30;
                    }
                    else {
                        tmp.hitbox[t].x = 770;
                        tmp.hitbox[t].w = 45;
                    }
                }
            }

            if (tmp.type == 2) {
                tmp.hitbox[0].x = 800;
                tmp.hitbox[0].y = 250;
                tmp.hitbox[0].w = 20;
                tmp.hitbox[0].h = 10;

                tmp.hitbox[1].x = 820;
                tmp.hitbox[1].y = 240;
                tmp.hitbox[1].w = 31;
                tmp.hitbox[1].h = 30;
            }

            if (tmp.type == 0) {
                for (int t = 0; t < 2; t++) {
                    tmp.hitbox[t].x = 800;
                    tmp.hitbox[t].y = 270;
                    tmp.hitbox[t].w = 31;
                    tmp.hitbox[t].h = 40;
                }
            }
            b.push_back(tmp);
        }

        if (b.size() >= 1 && rd() % 60 == 0 && b.back().hitbox[0].x <= 600) {
            vatcan tmp;
            tmp.type = rd() % 3;

            if (tmp.type == 1) {
                for (int t = 0; t < 2; t++) {
                    tmp.hitbox[t].y = 270;
                    tmp.hitbox[t].h = 43;
                    int x = rd() % 3;
                    if (x == 0) {
                        tmp.hitbox[t].x = 800;
                        tmp.hitbox[t].w = 15;
                    }
                    else if (x == 1) {
                        tmp.hitbox[t].x = 785;
                        tmp.hitbox[t].w = 30;
                    }
                    else {
                        tmp.hitbox[t].x = 770;
                        tmp.hitbox[t].w = 45;
                    }
                }
            }

            if (tmp.type == 2) {
                tmp.hitbox[0].x = 800;
                tmp.hitbox[0].y = 250;
                tmp.hitbox[0].w = 20;
                tmp.hitbox[0].h = 10;

                tmp.hitbox[1].x = 820;
                tmp.hitbox[1].y = 240;
                tmp.hitbox[1].w = 31;
                tmp.hitbox[1].h = 30;
            }

            if (tmp.type == 0) {
                for (int t = 0; t < 2; t++) {
                    tmp.hitbox[t].x = 800;
                    tmp.hitbox[t].y = 270;
                    tmp.hitbox[t].w = 31;
                    tmp.hitbox[t].h = 40;
                }
            }
            b.push_back(tmp);
        }
        graphics.presentScene();
        if (b.size() && b[0].hitbox[0].x + b[0].hitbox[0].w <= 0) {
            xoa++;

        }
        while (xoa--) {
            b.erase(b.begin());
        }
        //thua

        int cnt = 0;
        if (quit == false) {
            cnt = 0;

        }

        while (quit) {
            Mix_PauseMusic();
            SDL_RenderClear(graphics.renderer);
            graphics.renderTexture(background.texture, 0, 0);
            graphics.renderTexture(gameover, 230, 100);
            graphics.renderTexture(Score, 0, 0);
            graphics.renderTexture(High, 0, 20);

            score = 0;
            if (cnt == 0) {
                play(am_thanh_thua);
                cnt++;
            }
            graphics.renderTexture(thuadung, 0, Y);
            for (auto& i : b) {

                if (i.type == 1) {

                    graphics.renderTexture(coc, i.hitbox[0].x - 23, i.hitbox[0].y - 25);
                    if (i.hitbox[0].w > 15) {
                        graphics.renderTexture(coc, i.hitbox[0].x - 8, i.hitbox[0].y - 25);
                    }
                    if (i.hitbox[0].w > 30) {
                        graphics.renderTexture(coc, i.hitbox[0].x + 7, i.hitbox[0].y - 25);
                    }

                }
                else {
                    if (i.type == 2) {
                        if ((time % 50) > 24) {

                            i.hitbox[0].y -= 10;
                        }

                        graphics.renderTexture(chim[(time % 50) > 24], i.hitbox[0].x, i.hitbox[0].y - 11);

                        if ((time % 50) > 24) {
                            i.hitbox[0].y += 10;
                        }
                    }
                    else {
                        graphics.renderTexture(hopqua, i.hitbox[0].x - 5, i.hitbox[0].y - 5);
                    }
                }
            }


            graphics.renderTexture(reset, 350, 250);
            //nut rest
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
                    v = vtmp;
                    Y = 254;
                    quit = false;

                    b.clear();
                }
            }
            if (e.button.button == SDL_SCANCODE_ESCAPE) {
                quit = false;
                playGame = false;
				b.clear();
            }
            if (e.type == SDL_QUIT) {
                graphics.thoat();
            }
            graphics.presentScene();
            SDL_RenderPresent(graphics.renderer);
            graphics.prepareScene();
        }

    }

    graphics.thoat();

    return 0;
}
