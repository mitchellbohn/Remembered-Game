#include <iostream>

#include "SDL2\SDL.h"

using namespace std;

class Window {
	protected:
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool done;
	public:
	SDL_Renderer* getRenderer() { return renderer; }
	void init() {
		done=false;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow(
			"Remembered",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1920,
			1080,
			SDL_WINDOW_OPENGL
		);
		if (window == NULL) {
			cout << "Could not create window:\n" << SDL_GetError() << endl;
			done = false;
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			cout << "Could not create renderer:\n" << SDL_GetError() << endl;
			done = false;
			return;
		}
	}
	void exit() {
		if (done) return;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};

class Game:public Window {
	
};

Game Remembered;

int main(int argc, char* argv[]) {
	Remembered.init();
	Remembered.exit();
	return 0;
}
