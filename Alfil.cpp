#include "Alfil.h"
#include "Enum.h"

Alfil::Alfil(ENUM_COLOR color): Piece(color){
  this->color = color;
  Piece::setType(ALFIL);
}

char Alfil::toString(){
  return 'A';
}

bool Alfil::isValidMove(Position* origen, Position* destino){

}