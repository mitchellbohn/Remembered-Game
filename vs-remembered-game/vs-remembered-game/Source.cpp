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
#include "player.hpp"
#include "game.hpp"

using namespace std;

class NewGame : public Game {
	void setup() {
		Sprite *back = new Sprite();
		back->init(this, "Back", 1);
		back->setup();
		add(back);
		Player *player = new Player();
		player->init(this, "Player", 4);
		player->setup();
		//player->setVX(20.0); 
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
