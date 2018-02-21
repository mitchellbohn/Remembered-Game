#include <iostream>
#include <vector>
#include <sstream>

#include "SDL2\SDL.h"

using namespace std;

class Window {
  protected:
	int X, Y;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool done;
	//bool dead;
  public:
	int getX() {return X;}
	int getY() {return Y;}
	SDL_Renderer* getRenderer() { return renderer; }
	void init(int nX=640, int nY=480) {
		X=nX;
		Y=nY;
		done=false;
		//dead=false;
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
		//bool dead = false;
		while (/*!dead && */!done) {
			SDL_Event event;
			float dt=((float)SDL_GetTicks()-last)/1000.0;
			last = SDL_GetTicks();
			loop(dt);
			SDL_RenderPresent(renderer);
			if (SDL_PollEvent(&event)) {
				eventHandler(event);
			}
<<<<<<< HEAD
			SDL_Delay(1000/60);
=======
>>>>>>> 4d359430a54d145ef6647f04a4ae73198c36d065
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

class Animation {
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
	void cleanup(){ SDL_DestroyTexture(texture); }
};

class Sprite {
  protected:
	Window *win;
	string file;
	int w, h, count;
	bool done;
	float vX, vY, pX, pY, T0;
	vector <Animation> frames;
	int totalAnimationTime, totalGameTime;
  public:
	float getVX() { return vX; }
	float getVY() { return vY; }
	float getPX() { return pX; }
	float getPY() { return pY; }
	void add(Animation anim) {
		frames.push_back(anim);
		totalAnimationTime+=anim.getTime();
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
			Animation anim;
			stringstream sstring;
			sstring << file << i << ".bmp";
			anim.setup(win, sstring.str().c_str(), 333);
			add(anim);
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
	void exit() {}
};

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
		totalGameTime=newT0;
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
<<<<<<< HEAD
	Remembered.init(1920, 1080);
=======
	Remembered.init(1280, 720);
>>>>>>> 4d359430a54d145ef6647f04a4ae73198c36d065
	Remembered.run();
	Remembered.exit();
	return 0;
}
