#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "sprite.hpp"

class Player :public Sprite {
public:
	void init(Window *newWin,
		string newFile,
		int newCount,
		float newAX = 0.0,
		float newAY = 0.0,
		float newVX = 0.0,
		float newVY = 0.0,
		float newPX = 64.0,
		float newPY = 256.0,
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
