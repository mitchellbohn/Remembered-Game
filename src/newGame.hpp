#ifndef NEWGAME_HPP
#define NEWGAME_HPP

#include "game.hpp"

class NewGame : public Game {
	void setup() {
		Sprite *back = new Sprite();
		back->init(this, "Back", 1);
		back->setup();
		add(back);
		Sprite *floor = new Sprite();
		floor->init(this, "Floor", 1, 0.0, 0.0, 0.0, 0.0, 0.0, 576.0, 0);
		floor->setup();
		add(floor);
		Player *player = new Player();
		player->init(this, "Player", 4);
		player->setup();
		add(player);
	}
	void eventHandler(SDL_Event event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: done = true;
			case SDLK_a: chars[2]->setVX(-250.0); break;
			case SDLK_d: chars[2]->setVX(250.0); break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_a: chars[2]->setVX(0.0); break;
			case SDLK_d: chars[2]->setVX(0.0); break;
			}
		}
	}
	void cleanup() {}
	
	static int startPhysicsLoop(void *NewGamePtr) {
		NewGame *n=(NewGame *)NewGamePtr;
		float last=SDL_GetTicks();
		while (!n->done) {
			float dt = ((float)SDL_GetTicks() - last) / 1000.0;
			last=SDL_GetTicks();
			n->physicsLoop(dt);
			int ms=1000/60-dt*1000;
			if (ms<0) ms=0;
			SDL_Delay(ms);
		}
		return 0;
	}
	
	static int startRenderLoop(void *NewGamePtr) {
		NewGame *n=(NewGame *)NewGamePtr;
		float last=SDL_GetTicks();
		while (!n->done) {
			float dt = ((float)SDL_GetTicks() - last) / 1000.0;
			last=SDL_GetTicks();
			n->renderLoop(dt);
			int ms=1000/60-dt*1000;
			if (ms<0) ms=0;
			SDL_Delay(ms);
		}
		return 0;
	}
};
#endif
