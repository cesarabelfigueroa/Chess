#ifndef ALFIL_H
#define ALFIL_H
#include "Piece.h"
#include "Position.h"

class Alfil: public Piece {
private:
	ENUM_COLOR color;
public:
	Alfil(ENUM_COLOR);
	char toString();
	bool isValidMove(Position*, Position*);
};

#endif