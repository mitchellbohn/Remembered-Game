#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <sstream>

#include "animation.hpp"

class Sprite {
protected:
	Window *win;
	string file;
	int w, h, count;
	bool done;
	float aX, aY, vX, vY, pX, pY, T0;
	vector <Animation> frames;
	int animationTime, gameTime;
public:
	float getVX() { return vX; }
	float getVY() { return vY; }
	float getPX() { return pX; }
	float getPY() { return pY; }
	void add(Animation anim) {
		frames.push_back(anim);
		animationTime += anim.getTime();
	}
	virtual void loop(float dt) {
		vX = vX + aX * dt;
		vY = vY + aY * dt;
		pX = pX + vX * dt;
		pY = pY + vY * dt;
		gameTime += (int)(dt*1000.0);
	};
	virtual void cleanup() {
		for (unsigned i=0;i<frames.size();i++) {
			frames[i].cleanup();
		}
	}
	bool isDone(){ return done; }
	void init(Window *newWin, string newFile, int newCount = 1,
		float newAX = 0.0, 
		float newAY = 0.0,
		float newVX = 0.0,
		float newVY = 0.0,
		float newPX = 0.0,
		float newPY = 0.0,
		int newT0 = 0) {
		win = newWin;
		file = newFile;
		w = 0;
		h = 0;
		count = newCount;
		gameTime = newT0;
		animationTime = 0;
		aX = newAX;
		aY = newAY;
		vX = newVX;
		vY = newVY;
		pX = newPX;
		pY = newPY;
	}
	virtual void setup() {
		for (int i = 0; i<count; i++) {
			Animation anim;
			stringstream sstring;
			sstring << file << i << ".bmp";
			anim.setup(win, sstring.str().c_str(), 333);
			add(anim);
		}
	}
	void render() {
		if (frames.size() == 0) return;
		if (frames.size() == 1) {
			frames[0].render(win, pX, pY);
			return;
		}
		int withinFrame;
		withinFrame = gameTime % animationTime;
		int talley = 0;
		for (int i = 0; i<frames.size(); i++) {
			talley += frames[i].getTime();
			if (withinFrame<talley) {
				frames[i].render(win, pX, pY);
				break;
			}
		}
	}
	void exit() {}
};
#endif
