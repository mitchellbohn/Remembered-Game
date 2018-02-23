#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <SDL.h>

using namespace std;

class Window {
protected:
	int X, Y;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool done;
public:
	int getX() { return X; }
	int getY() { return Y; }
	SDL_Renderer* getRenderer() { return renderer; }
	void init(int nX = 640, int nY = 480) {
		X = nX;
		Y = nY;
		done = false;
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("Remembered", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, X, Y, SDL_WINDOW_OPENGL
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
	virtual void setup() = 0;
	virtual void loop(float dt) = 0;
	virtual void cleanup() = 0;
	virtual void eventHandler(SDL_Event e) = 0;
	void run() {
		setup();
		float last = SDL_GetTicks();
		while (!done) {
			SDL_Event event;
			float dt = ((float)SDL_GetTicks() - last) / 1000.0;
			last = SDL_GetTicks();
			loop(dt);
			SDL_RenderPresent(renderer);
			if (SDL_PollEvent(&event)) {
				eventHandler(event);
			}
			SDL_Delay(1000 / 60);
		}
		if (!done) cleanup();
	}
	void exit() {
		if (done) return;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
};
#endif
