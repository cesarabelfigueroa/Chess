#ifndef DAMA_H
#define DAMA_H
#include "Piece.h"
#include "Position.h"

class Dama: public Piece{
	private:
	ENUM_COLOR color;
	public:
	Dama(ENUM_COLOR);
	char toString();
	bool isValidMove(Position*, Position*);
};

#endif