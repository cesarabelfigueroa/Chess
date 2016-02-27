#include "Torre.h"
#include "Enum.h"

Torre::Torre(ENUM_COLOR color): Piece(color){
  this-> color = color;
  Piece::setType(TORRE);
}

char Torre::toString(){
  return 'T';
}

bool Torre::isValidMove(Position* origen, Position* destino){

}