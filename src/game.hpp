#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"

class Game :public Window {
protected:
	vector <Sprite *> chars;
public:
	void add(Sprite *c) { chars.push_back(c); }
	void loop(float dt) {
		for (unsigned int i = 0; i<chars.size(); i++) { chars[i]->loop(dt); }
		for (unsigned int i = 0; i<chars.size(); i++) { chars[i]->render(); }
	}
};
#endif
