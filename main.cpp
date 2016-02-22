#include <iostream>
#include <curses.h>
#include "Position.h"

using std::cout;
using std::endl;

int main(int argc, char const *argv[]){
	Position* posicion = new Position(3,2);
	cout << posicion -> Position::getY() << endl;
	delete posicion;

  

	return 0;
}
