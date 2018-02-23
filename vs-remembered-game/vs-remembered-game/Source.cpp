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

class NewGame : public Game {
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
		//player->setVX(20.0); 
		add(player);
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