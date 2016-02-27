#include "Rey.h"
#include "Enum.h"

Rey::Rey(ENUM_COLOR color): Piece(color){
  this-> color = color;
  Piece::setType(REY);
}

char Rey::toString(){
  return 'R';
}

bool Rey::isValidMove(Position* origen, Position* destino){

}