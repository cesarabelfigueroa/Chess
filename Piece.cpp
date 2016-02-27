#include "Piece.h"
#include "Position.h"

Piece::Piece(ENUM_COLOR color){
   this->color = color;
   Piece::setType(VACIA);
}
 
ENUM_TYPE Piece::getType(){
   return type;
}

ENUM_COLOR Piece::getColor(){
   return color;
}

char Piece::toString(){
	return ' ';
}

bool Piece::isValidMove(Position* origen, Position* destino){

}

void Piece::setType(ENUM_TYPE type){
   this->type = type;
}