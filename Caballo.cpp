#include "Caballo.h"
#include "Enum.h"

Caballo::Caballo(ENUM_COLOR color): Piece(color){
  this->color = color;
  Piece::setType(CABALLO);
}

char Caballo::toString(){
  return 'C';
}

bool Caballo::isValidMove(Position* origen, Position* destino){

}