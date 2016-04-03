#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include "Enum.h"

class Piece {
private:
   ENUM_TYPE type;
   ENUM_COLOR color;
public:
   Piece(ENUM_COLOR);
   ENUM_TYPE getType();
   ENUM_COLOR getColor();
   virtual char toString();
   virtual bool isValidMove(Position*, Position*);
protected:
   void setType(ENUM_TYPE);
};

#endif