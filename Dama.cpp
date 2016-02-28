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
	int initX = origen -> getX();
	int initY = origen -> getY(); 
	int endX = destino -> getX();
	int endY = destino -> getY();
	if(initX + initY == endX + endY){
		return true;
	}else if(initX - initY == endX - endY){
		return true;
	}else if(initX == endX && initY != endY){
		return true;
	}else if(initY == endY && initX != endX){
		return true;
	}else{
		return false;
	}
}