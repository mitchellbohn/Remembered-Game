/* TO-DO:
 * 'a' & 'd' movements
 * platform 'collision'
 * 'w' & 's' movements
 * side-scrolling
 * second map-state 'e'
 */

#include "newGame.hpp"

NewGame Remembered;

int main(int argc, char* argv[]) {
	Remembered.init(1920, 1080);
	Remembered.run();
	Remembered.exit();
	return 0;
}
