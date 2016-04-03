#ifndef TORRE_H
#define TORRE_H
#include "Piece.h"
#include "Position.h"

class Torre: public Piece {
private:
	ENUM_COLOR color;
public:
	Torre(ENUM_COLOR);
	char toString();
	bool isValidMove(Position*, Position*);
};

#endif