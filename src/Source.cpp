#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>

#include <SDL.h>

#define DEBUG(s) //cerr << s << endl;

using namespace std;


class ProtoGame {
	
};

class AnimationFrame {
	
};

class Sprite {

};

class Ball:public Sprite {

};

class Game:public ProtoGame {
	
};

class TheGame: public Game {
	
};

TheGame MyGame;

int main(int argc, char* argv[]) {
	MyGame.init("MyGame", 640, 480);
	DEBUG("After init ");
	MyGame.run();
	MyGame.exit();
	return 0;
}
