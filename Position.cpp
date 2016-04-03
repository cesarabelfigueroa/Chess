#include "Position.h"

Position::Position(int x, int y) {
	this -> x = x;
	this -> y = y;
}

Position::~Position() {

}

int Position::getX() {
	return x;
}

void Position::setX(int x) {
	this -> x = x;
}

int Position::getY() {
	return y;
}

void Position::setY(int y) {
	this -> y = y;
}