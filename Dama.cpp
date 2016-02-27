#include "Dama.h"
#include "Enum.h"

Dama::Dama(ENUM_COLOR color): Piece(color){
  this->color = color;
  Piece::setType(DAMA);
}

char Dama::toString(){
  return 'D';
}

bool Dama::isValidMove(Position* origen, Position* destino){

}