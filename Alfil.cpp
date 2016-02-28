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
	int initX = origen -> getX();
	int initY = origen -> getY();
	int endX = destino -> getX();
	int endY = destino -> getY();
	if(initX + initY == endX + endY){
		return true;
	}else if(initX - initY == endX - endY){
		return true;
	}else{
		return false;
	}

}