#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>

#include "SDL2\SDL.h"

#define DEBUG(s)

using namespace std;

class Window {
  protected:
	int X, Y;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool done;
	bool dead;
  public:
	int getX() {return X;}
	int getY() {return Y;}
	SDL_Renderer* getRenderer() { return renderer; }
	void init(int newX=640, int newY=480) {
		X=newX;
		Y=newY;
		done=false;
		dead=false;
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
		bool dead = false;
		while (!dead && !done) {
			SDL_Event event;
			float dt=((float)SDL_GetTicks()-last)/1000.0;
			last = SDL_GetTicks();
			loop(dt);
			SDL_RenderPresent(renderer);
			if (SDL_PollEvent(&event)) {
				eventHandler(event);
			}
			//SDL_Delay(1000/60);
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

class AnimationFrame {
	SDL_Texture *texture;
	Window *win;
	int w, h, time;
	bool done;
  public:
	int getTime() { return time; }
	void render(Window *win, int x, int y) {
		SDL_Rect src, dest;
		src.x=(int)0; src.y=(int)0; src.w=w; src.h=h;
		dest.x=(int)x; dest.y=(int)y; dest.w=w; dest.h=h;
		SDL_RenderCopy(win->getRenderer(), texture, &src, &dest);
	}
	void setup(Window *newWin, string file, int newTime) {
		done = false;
		win = newWin;
		time = newTime;
		SDL_Surface *image=SDL_LoadBMP(file.c_str());
		if (image == NULL) {
			cout << "Could not create image:\n" << SDL_GetError() << endl;
			done = true;
			return;
		}
		SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 255));
		texture=SDL_CreateTextureFromSurface(win->getRenderer(), image);
		if (texture == NULL) {
			cout << "Could not create texture:\n" << SDL_GetError() << endl;
			done = true;
			return;
		}
		SDL_FreeSurface(image);
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	}
	void cleanup() {
		SDL_DestroyTexture(texture);
	}
};

class Sprite {
  protected:
	Window *win;
	string file;
	int w, h, count;
	bool done;
	float vX, vY, pX, pY, T0;
	vector <AnimationFrame> frames;
	int totalAnimationTime, totalGameTime;
  public:
	float getVX() { return vX; }
	float getVY() { return vY; }
	float getPX() { return pX; }
	float getPY() { return pY; }
	void add(AnimationFrame af) {
		frames.push_back(af);
		totalAnimationTime+=af.getTime();
	}
	void loop(float dt) {
		pX=pX+vX*dt;
		pY=pY+vY*dt;
		totalGameTime+=(int)(dt*1000.0);
	};
	void init(Window *newWin, string newFile, int newCount = 1, 
		float newVX=0.0,
		float newVY=0.0,
		float newPX=0.0,
		float newPY=0.0,
		int newT0=0) {
		win = newWin;
		file=newFile;
		w=0;
		h=0;
		count = newCount;
		totalGameTime=newT0;
		totalAnimationTime=0;
		vX=newVX;
		vY=newVY;
		pX=newPX;
		pY=newPY;
	}
	void setup(){
		for (int i = 0; i<count; i++) {
			AnimationFrame af;
			stringstream sstring;
			sstring << file << i << ".bmp";
			af.setup(win, sstring.str().c_str(), 333);
			add(af);
		}
	}
	void render() {
		if (frames.size()==0) return;
		if (frames.size()==1) {
			frames[0].render(win, pX, pY);
			return;
		}
		int withinFrame;
		withinFrame=totalGameTime % totalAnimationTime;
		int talley = 0;
		for (int i=0; i<frames.size(); i++) {
			talley+=frames[i].getTime();
			if (withinFrame<talley) {
				frames[i].render(win, pX, pY);
				break;
			}
		}
	}
	void exit() {
		
	}
};

class Player:public Sprite {
	public:
	void init(Window *newWin,
	string newFile,
	int newCount,
	float newVX=0.0,
	float newVY=0.0,
	float newPX=128.0,
	float newPY=512.0,
	int newT0=0) {
		win=newWin;
		file=newFile;
		vX=newVX;
		vY=newVY;
		pX=newPX;
		pY=newPY;
		count=newCount;
		totalGameTime=newT0;
	}
};

class Game:public Window {
  protected:
	vector <Sprite *> characters;
	vector <Player *> player;
	public:
	void add(Sprite *c) { characters.push_back(c); }
	void loop(float dt) {
		for (unsigned int i=0; i<characters.size(); i++) {
			characters[i]->loop(dt);
		}
		for (unsigned int i=0; i<characters.size(); i++) {
			characters[i]->render();
		}
	}
	void eventHandler(SDL_Event e) {
		if( e.type == SDL_KEYDOWN ) {
			switch( e.key.keysym.sym ) {
				case SDLK_a: vX = -5; break;
				case SDLK_d: vX = 5; break;
			}    
		}
		else if( e.type == SDL_KEYUP ) {
			switch( e.key.keysym.sym ) {
				case SDLK_a: vX = 5; break;
				case SDLK_d: vX = -5; break;
			}        
		}
	}
};

class TheGame: public Game {
	void setup() {
		DEBUG("In Setup");
		Sprite *back = new Sprite();
		back->init(this, "Back", 1);
		back->setup();
		add(back);
		Player *player = new Player();
		player->init(this, "Player", 4);
		player->setup();
		add(player);
	}
	void eventHandler(SDL_Event e) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym==SDLK_ESCAPE) {
				done=true;
			}
		}
	}
	void cleanup() {
	}
};

TheGame Remembered;

int main(int argc, char* argv[]) {
	Remembered.init(1920, 1080);
	DEBUG("After init ");
	Remembered.run();
	Remembered.exit();
	return 0;
}
