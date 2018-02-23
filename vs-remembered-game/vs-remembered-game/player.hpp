#ifndef PLAYER_HPP
#define PLAYER_HPP


class Player :public Sprite {
public:
	void setVX(float newVX) { vX = newVX; }
	void setVY(float newVY) { vY = newVY; }
	void setPX(float newPX) { pX = newPX; }
	void setPY(float newPY) { pY = newPY; }
	void init(Window *newWin,
		string newFile,
		int newCount,
		float newVX = 0.0,
		float newVY = 0.0,
		float newPX = 32.0,
		float newPY = 128.0,
		int newT0 = 0) {
		win = newWin;
		file = newFile;
		vX = newVX;
		vY = newVY;
		pX = newPX;
		pY = newPY;
		count = newCount;
		gameTime = newT0;

	}
};
#endif