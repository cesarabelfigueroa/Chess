/*---- Standard C++ directives ----*/
#include <iostream>
#include <curses.h>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <curses.h>

/*---- NCurses directives ----*/
#include <menu.h>
#include <ncurses.h>

/*---- Chess directives ----*/
#include "Position.h"
#include "Piece.h"
#include "Alfil.h"
#include "Caballo.h"
#include "Dama.h"
#include "Peon.h"
#include "Rey.h"
#include "Torre.h"

/*---- Namespaces ----*/
using std::cout;
using std::cin;
using std::endl;
using std::isalpha;
using std::isdigit;
using std::string;

/*---- Functions Headers ----*/
bool isValiEntry(string move);
Position* createPosition(char, char);
int valueOfChar(char);

int main(int argc, char const *argv[]){

	Piece* pieza = new Peon(NEGRO);
	cout << pieza-> getType() << endl;
	Piece* pieza2 = new Alfil(NEGRO);
	cout << pieza2 -> getType() << endl;
	Piece* pieza3 = new Caballo(NEGRO);
	cout << pieza3 -> getType() << endl;
	Piece* pieza4 = new Torre(NEGRO);
	cout << pieza4 -> getType() << endl;
	Piece* pieza5 = new Rey(NEGRO);
	cout << pieza5 -> getType() << endl;
	Piece* pieza6 = new Dama(NEGRO);
	cout << pieza6 -> getType() << endl;

	/*if(isValiEntry(move)){
		Position* initial = createPosition(move[0], move[1]);
		Position* final = createPosition(move[2], move[3]);
		cout << initial -> getX() << endl;
		cout << initial -> getY() << endl;
		initial -> ~Position();
		initial -> ~Position();
	}else{
		cout << "Es inválido." << endl;
	}*/

	return 0;
}

Position* createPosition(char x, char y){
	int file = valueOfChar(x);
	int column = valueOfChar(y);
	Position* position = new Position(file, column);
	return position;
}

int valueOfChar(char character){
	if(isalpha(character)){
		if(character == 'a'){
			return 0;
		}else if(character == 'b'){
			return 1;
		}else if(character == 'c'){
			return 2;

		}else if(character == 'd'){
			return 3;

		}else if(character == 'e'){
			return 4;

		}else if(character == 'f'){
			return 5;

		}else if(character == 'g'){
			return 6;

		}else if(character == 'h'){
			return 7;
		}else{
			return -1;
		}
	}else if(isdigit(character)){
		char number[] = {character};
		return atoi(number);
	}else{
		return -1;
	}
}

bool isValiEntry(string move){
	for (int i = 0; i < move.length(); ++i){
		if(valueOfChar(move[i]) == -1){
			return false;
		}
	}
	return true;
}