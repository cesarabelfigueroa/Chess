#include "Peon.h"
#include "Enum.h"
#include "ncurses.h"

Peon::Peon(ENUM_COLOR color): Piece(color){
  this-> color = color;
  Piece::setType(PEON);
}

char Peon::toString(){
  return 'P';
}

bool Peon::isValidMove(Position* origen, Position* destino){
	int initX = origen -> getX();
	int initY = origen -> getY();
	int endX = destino -> getX();
	int endY = destino -> getY();
	if(initY == endY){
		if(color == BLANCO){
			if(initX == 6 && initX <= endX + 2  && endY == initY){
				return true;
			}else if(initX != 6 && initX == endX + 1 && endY == initY){
				return true;
			}else{
				return false;
			}
		}else if(color == NEGRO){
			if(initX == 1 && endX <= initX + 2 && endY == initY){
				return true;
			}else if(initX != 1 && endX == initX+1 && endY == initY){
				return true;
			}else{
				return false;
			}
		}
	}else{
		return false;
	}
}