#include "Peon.h"
#include "Enum.h"

Peon::Peon(ENUM_COLOR color): Piece(color){
  this-> color = color;
  Piece::setType(PEON);
}

char Peon::toString(){
  return 'P';
}

bool Peon::isValidMove(Position* origen, Position* destino){

}