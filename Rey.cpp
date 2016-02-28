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
	int initX = origen -> getX();
	int initY = origen -> getY(); 
	int endX = destino -> getX();
	int endY = destino -> getY();
	if((endY == initY + 1 || endY == initY || endY == initY -1) && (endX == initX - 1 || endX == initX || endX == initX + 1)){
		return true;
	}else{
		return false;
	}
}