/* 'a' & 'd' movements
 * 'w' & 's' movements
 * floor
 * side-scrolling
 */


#include <iostream>
#include <vector>
#include <sstream>

#include <SDL.h>

#include "window.hpp"
#include "animation.hpp"
#include "sprite.hpp"

using namespace std;

class Player:public Sprite {
public:
	void setVX(float newVX) { vX = newVX; }
	void setVY(float newVY) { vY = newVY; }
	void setPX(float newPX) { pX = newPX; }
	void setPY(float newPY) { pY = newPY; }
	void init(Window *newWin,
	string newFile,
	int newCount,
	float newVX=0.0,
	float newVY=0.0,
	float newPX=32.0,
	float newPY=128.0,
	int newT0=0) {
		win=newWin;
		file=newFile;
		vX=newVX;
		vY=newVY;
		pX=newPX;
		pY=newPY;
		count=newCount;
		gameTime=newT0;
		
	}
	void eventHandler(SDL_Event event) {
			if (event.type == SDL_KEYDOWN) {
				switch( event.key.keysym.sym ) {
					case SDLK_a: vX = 30.0; break;
					//case SDLK_d: player->setVX(speed); break;
				}
			}
			else if( event.type == SDL_KEYUP ) {
				switch( event.key.keysym.sym ) {
					//case SDLK_a: Player->setVX(speed); break;
					//case SDLK_d: Player->setVX(speed); break;
				}        
			}
	}
	void run() {
		float last = SDL_GetTicks();
		while (!done) {
			SDL_Event event;
			float dt=((float)SDL_GetTicks()-last)/1000.0;
			last = SDL_GetTicks();
			loop(dt);
			//SDL_RenderPresent(renderer);
			if (SDL_PollEvent(&event)) {
				eventHandler(event);
			}
			SDL_Delay(1000/60);
		}
		//if (!done) cleanup();
	}
};

class Game:public Window {
protected:
	vector <Sprite *> chars;
	vector <Player *> player;
public:
	void add(Sprite *c) { chars.push_back(c); }
	void loop(float dt) {
		for (unsigned int i=0;i<chars.size();i++){chars[i]->loop(dt);}
		for (unsigned int i=0;i<chars.size();i++){chars[i]->render();}
	}
};

class NewGame: public Game {
public:
	void setup() {
		Sprite *back = new Sprite();
		back->init(this, "Back", 1);
		back->setup();
		add(back);
		//Sprite *floor = new Sprite();
		//floor->init(this, "Plat", 1);
		Player *player = new Player();
		player->init(this, "Player", 4);
		player->setup();
		player->run();
		//player->setVX(20.0); 
		add(player);
	}
	void eventHandler(SDL_Event event) {
		if (event.type == SDL_KEYDOWN) {
			switch( event.key.keysym.sym ) {
				case SDLK_ESCAPE: done=true;
			}
		}
	}
	void cleanup() {}
};

NewGame Remembered;

int main(int argc, char* argv[]) {
	Remembered.init(1280, 720);
	Remembered.run();
	Remembered.exit();
	return 0;
}
