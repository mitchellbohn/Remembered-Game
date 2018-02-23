/* 'a' & 'd' movements
* 'w' & 's' movements
* floor
* side-scrolling
*/

#include "newGame.hpp"

NewGame Remembered;

int main(int argc, char* argv[]) {
	Remembered.init(1920, 1080);
	Remembered.run();
	Remembered.exit();
	return 0;
}
