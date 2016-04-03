#ifndef PEON_H
#define PEON_H
#include "Piece.h"
#include "Position.h"

class Peon: public Piece {
private:
	ENUM_COLOR color;
public:
	Peon(ENUM_COLOR);
	char toString();
	bool isValidMove(Position*, Position*);
};

#endif