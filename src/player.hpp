#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "sprite.hpp"

class Player :public Sprite {
public:
	void setAX(float newAX) { aX = newAX; }
	void setAY(float newAY) { aY = newAY; }
	void setVX(float newVX) { vX = newVX; }
	void setVY(float newVY) { vY = newVY; }
	void setPX(float newPX) { pX = newPX; }
	void setPY(float newPY) { pY = newPY; }
	void init(Window *newWin,
		string newFile,
		int newCount,
		float newAX = 0.0,
		float newAY = 0.0,
		float newVX = 0.0,
		float newVY = 0.0,
		float newPX = 128.0,
		float newPY = 512.0,
		int newT0 = 0) {
		win=newWin;
		file=newFile;
		aX=newAX;
		aY=newAY;
		vX=newVX;
		vY=newVY;
		pX=newPX;
		pY=newPY;
		count=newCount;
		gameTime=newT0;
	}
	void loop(float dt) {
		Sprite::loop(dt);
	}
};
#endif
