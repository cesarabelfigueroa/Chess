#include "Caballo.h"
#include "Enum.h"

Caballo::Caballo(ENUM_COLOR color): Piece(color) {
	this->color = color;
	Piece::setType(CABALLO);
}

char Caballo::toString() {
	return 'C';
}

bool Caballo::isValidMove(Position* origen, Position* destino) {
	int initX = origen -> getX();
	int initY = origen -> getY();
	int endX = destino -> getX();
	int endY = destino -> getY();
	if (endX == initX - 2 && (endY == initY - 1 || endY == initY + 1 )) {
		return true;
	} else if (endX == initX + 2 && (endY == initY + 1 || endY == initY - 1 )) {
		return true;
	} else if (endY == initY - 2 && (endX == initX + 1 || endX == initX - 1 )) {
		return true;
	} else if (endY == initY + 2 && (endX == initX - 1 || endX == initX + 1)) {
		return true;
	}
	else {
		return false;
	}
}