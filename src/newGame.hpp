#ifndef NEWGAME_HPP
#define NEWGAME_HPP

#include "game.hpp"

class NewGame : public Game {
	vector <Player *> player;
	void setup() {
		Sprite *back = new Sprite();
		back->init(this, "Back", 1);
		back->setup();
		add(back);
		Sprite *floor = new Sprite();
		floor->init(this, "Floor", 1, 0.0, 0.0, 0.0, 0.0, 0.0, 832.0, 0);
		floor->setup();
		add(floor);
		Player *player = new Player();
		player->init(this, "Player", 4);
		player->setup();
		add(player);
		player->setVX(250.0); //Player move example
	}
	void eventHandler(SDL_Event event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: done = true;
			//case SDLK_a: player->setVX(-250.0); break;
			//case SDLK_d: player->setVX(250.0); break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			//case SDLK_a: /*player->setVX(0.0); break;
			//case SDLK_d: /*player->setVX(0.0); break;
			}
		}
	}
	void cleanup() {}
};
#endif
