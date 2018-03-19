/* TO-DO:
 * platform 'collision'
 * side-scrolling
 * switch to second map-state with 'e'
 */

#include "newGame.hpp"

NewGame Remembered;

int main(int argc, char* argv[]) {
	Remembered.init(1280, 720);
	Remembered.run();
	Remembered.exit();
	return 0;
}
