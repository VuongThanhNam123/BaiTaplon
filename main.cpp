#include <SDL.h>
#include "graphics.h"
#include <iostream>
#include <vector>
#include <string>
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


    graphics.presentScene();
    ScrollingBackground background;
    background.setTexture(graphics.loadTexture("img\\nen.jpg"));
    SDL_Texture* coc=graphics.loadTexture("img\\coc.png");
	vector<vatcan> b;
    
    bool quit = false;
    int v = 1;
    int time = 0;
    SDL_Event e;
    SDL_Texture* character[7];

		character[0] = graphics.loadTexture("animation/go1.png");
        character[1] = graphics.loadTexture("animation/go2.png");
        character[2] = graphics.loadTexture("animation/go3.png");
        character[3] = graphics.loadTexture("animation/go4.png");
        character[4] = graphics.loadTexture("animation/go5.png");
        character[5] = graphics.loadTexture("animation/go6.png");
        character[6] = graphics.loadTexture("animation/go7.png");

		

    while (!quit) {
		
        time++;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            
        }
        
        background.scroll(v);
        graphics.render(background);
        graphics.renderTexture(character[(time/5)%7], 0, 254);
  //      graphics.renderTexture(coc, 50, 245);
		//SDL_Rect r = { 73, 270, 15, 50 };
		//SDL_RenderDrawRect(graphics.renderer, &r);
        
       if (time % 100 == 0 && v<75) {
           v++;
        }
	   for (auto &i : b) {
           if (i.type == 1) {
               graphics.renderTexture(coc, i.hitbox.x-23, i.hitbox.y-25);
			   i.hitbox.x -= 1;
           }
	   }
       
	   if (rd() % 100 == 0 && b.size()==0) {
		   vatcan tmp;
		   tmp.hitbox.x = 800;
		   tmp.hitbox.y = 270;
		   tmp.hitbox.w = 15;
		   tmp.hitbox.h = 50;
		   tmp.type = 1;
		   b.push_back(tmp);
	   }
	   if (rd() % 100 == 0 && b.size() && b.back().hitbox.x<=725 ) {
		   vatcan tmp;
		   tmp.hitbox.x = 800;
		   tmp.hitbox.y = 270;
		   tmp.hitbox.w = 15;
		   tmp.hitbox.h = 50;
		   tmp.type = 1;
		   b.push_back(tmp);

       }
       if (b.size() && b[0].hitbox.x <= 0) {
		   b.erase(b.begin());
       
       }
        graphics.presentScene();
        SDL_RenderClear(graphics.renderer);
        SDL_Delay(10);
        
    }
    SDL_DestroyTexture(background.texture);
    waitUntilKeyPressed();
    graphics.thoat();
    
    return 0;
}