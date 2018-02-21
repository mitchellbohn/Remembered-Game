#include <iostream>
#include <vector>
#include <sstream>

#include <SDL2/SDL.h>

#include "window.hpp"
#include "animation.hpp"
#include "sprite.hpp"

using namespace std;

class Player:public Sprite {
public:
	void init(Window *newWin,
	string newFile,
	int newCount,
	float newVX=0.0,
	float newVY=0.0,
	float newPX=64.0,
	float newPY=256.0,
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
	void setup() {
		Sprite *back = new Sprite();
		back->init(this, "Back", 1);
		back->setup();
		add(back);
		Player *player = new Player();
		player->init(this, "Player", 4);
		player->setup();
		add(player);
	}
	void eventHandler(SDL_Event event) {
		if (event.type == SDL_KEYDOWN) {
			switch( event.key.keysym.sym ) {
				case SDLK_ESCAPE: done=true;
				case SDLK_a: /*player vX = <0;*/ break;
				case SDLK_d: /*player vX = >0;*/ break;
			}
		}
		else if( event.type == SDL_KEYUP ) {
			switch( event.key.keysym.sym ) {
				case SDLK_a: /*player vX = 0;*/ break;
				case SDLK_d: /*player vX = 0;*/ break;
			}        
		}
	}
	void cleanup() {}
};

NewGame Remembered;

int main(int argc, char* argv[]) {
	Remembered.init(1920, 1080);
	Remembered.run();
	Remembered.exit();
	return 0;
}
