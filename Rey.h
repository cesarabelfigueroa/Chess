#ifndef REY_H
#define REY_H
#include "Piece.h"
#include "Position.h"

class Rey: public Piece {
private:
	ENUM_COLOR color;
public:
	Rey(ENUM_COLOR);
	char toString();
	bool isValidMove(Position*, Position*);
};

#endif