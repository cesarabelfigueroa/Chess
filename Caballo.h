#ifndef CABALLO_H
#define CABALLO_H
#include "Piece.h"
#include "Position.h"

class Caballo: public Piece {
private:
	ENUM_COLOR color;
public:
	Caballo(ENUM_COLOR);
	char toString();
	bool isValidMove(Position*, Position*);
};

#endif