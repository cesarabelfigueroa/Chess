#include "Torre.h"
#include "Enum.h"

Torre::Torre(ENUM_COLOR color): Piece(color) {
	this-> color = color;
	Piece::setType(TORRE);
}

char Torre::toString() {
	return 'T';
}

bool Torre::isValidMove(Position* origen, Position* destino) {
	int initX = origen -> getX();
	int initY = origen -> getY();
	int endX = destino -> getX();
	int endY = destino -> getY();
	if (initX == endX && initY != endY) {
		return true;
	} else if (initY == endY && initX != endX) {
		return true;
	} else {
		return false;
	}
}