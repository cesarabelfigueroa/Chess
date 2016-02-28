/*---- Standard C++ directives ----*/
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>

/*---- NCurses directives ----*/
#include <menu.h>
#include <panel.h>
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
bool isValiEntry(string);
void printArray(Piece***);
Position* createPosition(char, char);
int valueOfChar(char);
Piece*** createBoard();
void showBoard(Piece***);
void destroyBoard(Piece***);
void Mover(Piece***, Position* , Position*);
bool isSomethingInMiddle(Piece***, Position*, Position*);

int main(int argc, char *argv[]){
 	Piece*** board = createBoard();
 	Position* initial;
 	Position* end;
 	char* movimiento = new char[4];
 	int turno = 0;
	initscr();	
	start_color();
	init_pair(1, COLOR_BLACK, 0);
	init_pair(2, COLOR_WHITE, 0);
	while(true){	
		showBoard(board);
		printw("\t1. Mover. \n");
		printw("\t2. Guardar Partida. \n");
		printw("\t2. Salir. \n\n");
		printw("\t¿Qué desea hacer? : ");
		noecho();
		if(getch() == 49){
			clear();
			showBoard(board);
			if(turno % 2){
				printw("\tOpciones: Turno de las negras. \n\n");
			}else{
				printw("\tOpciones: Turno de las blancas. \n\n");
			}
			printw("\t¿Cuál es tu movimiento? : ");
			char valor = getch();
			while(!(((int) valor >= 65 && (int) valor <= 72) ||((valor >= 97)&& (valor <= 104)))){
				valor = getch();
			}
			movimiento[0] = valor;
			addch(valor);
			valor = getch();
			while(!(((int) valor >= 48 && (int) valor <= 55))){
				valor = getch();
			}
			movimiento[1] = valor;
			addch(valor);
			while(!(((int) valor >= 65 && (int) valor <= 72) ||((valor >= 97)&& (valor <= 104)))){
				valor = getch();
			}
			movimiento[2] = valor;
			addch(valor);
			valor = getch();
			while(!(((int) valor >= 48 && (int) valor <= 55))){
				valor = getch();
			}
			movimiento[3] = valor;
			addch(valor);
			initial = createPosition(movimiento[1], movimiento[0]);
			end = createPosition(movimiento[3], movimiento[2]);
			if(isValiEntry(movimiento)){
				if((board[initial -> getX()][initial -> getY()]) -> getType() == PEON){
					if((board[end -> getX()][end -> getY()]) -> getType() != VACIA){
						int initialX = initial -> getX();
						int initialY = initial -> getY();
						int endX = end -> getX();
						int endY = end -> getY();
						if((board[initial -> getX()][initial -> getY()]) -> getColor() == BLANCO){
							if(endX == initialX - 1 && endY == initialY + 1){
								Mover(board, initial , end);
							}else if(endX == initialX - 1 && endY == initialY - 1){
								Mover(board, initial , end);
							}
						}else if((board[initial -> getX()][initial -> getY()]) -> getColor() == NEGRO){
							if(endX == initialX + 1 && endY == initialY + 1){
								Mover(board, initial , end);
							}else if(endX == initialX + 1 && endY == initialY - 1){
								Mover(board, initial , end);
							}
						}
					}
				}
			}
			if(isValiEntry(movimiento) && !isSomethingInMiddle(board, initial, end) && ((board[initial -> getX()][initial -> getY()]) -> isValidMove(initial, end))){
				Mover(board, initial , end);
			}
			getch();
			turno++;
		}
		clear();
	}	
	destroyBoard(board);
	endwin();			
	return 0;
}

void showBoard(Piece*** board){
	printw("\n\n");
	printw("\t\t A \t B \t C \t D \t E \t F \t G \t H \t\n\n\n");
	for( int i = 0; i < 8; i++ ){
		printw("\t");
		addch(i + 48);
		printw("\t");
		for (int j = 0; j < 8; ++j){
			if(board[i][j]){
				printw("[");
				attron(COLOR_PAIR(board[i][j] -> getColor() + 1) | A_BOLD );
				addch(board[i][j] -> toString());
				attroff(COLOR_PAIR(board[i][j] -> getColor() + 1));
				printw("]");
			}else{
				printw("[");
				addch(' ');
				printw("]");
			}
			printw("\t");
		}
		printw("\n\n\n");
	}
}

void printArray(Piece*** board){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if(board[i][j]){
				cout << "[" << board[i][j] -> toString() << "] ";
			}else{
				cout << "[ ]";
			}
		}
		cout << endl;
	}
	cout << endl;
}

Position* createPosition(char x, char y){
	int file = valueOfChar(x);
	int column = valueOfChar(y);
	Position* position = new Position(file, column);
	return position;
}

int valueOfChar(char character){
	if(isalpha(character)){
		if(tolower(character) == 'a'){
			return 0;
		}else if(tolower(character) == 'b'){
			return 1;
		}else if(tolower(character) == 'c'){
			return 2;

		}else if(tolower(character) == 'd'){
			return 3;

		}else if(tolower(character) == 'e'){
			return 4;

		}else if(tolower(character) == 'f'){
			return 5;

		}else if(tolower(character) == 'g'){
			return 6;

		}else if(tolower(character) == 'h'){
			return 7;
		}else{
			return -1;
		}
	}else if(isdigit(character)){
		return ((int) character) - 48 ;
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

Piece*** createBoard(){
	Piece*** board = new Piece**[8];
	for (int i = 0; i < 8; ++i){
		board[i] = new Piece*[8];
	}

	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			ENUM_COLOR color = NULO;
			if(i == 0 || i == 1){
				color = NEGRO;
			}else if(i == 6 || i == 7){
				color = BLANCO;
			}
			if(i == 0 && j == 0 || i == 0 && j == 7 || i == 7 && j == 0 || i == 7 && j == 7){
				board[i][j] = new Torre(color);
			}else if(i == 0 && j == 1 || i == 0 && j == 6 || i == 7 && j == 1 || i == 7 && j == 6){
				board[i][j] =  new Caballo(color);
			}else if(i == 0 && j == 2 || i == 0 && j == 5 || i == 7 && j == 2 || i == 7 && j == 5){
				board[i][j] =  new Alfil(color);
			}else if(i == 0 && j == 3 || i == 7 && j == 3){
				board[i][j] = new Dama(color);
			}else if(i == 0 && j == 4 || i == 7 && j == 4){
				board[i][j] =  new Rey(color);
			}else if(i == 1 || i == 6){
				board[i][j] =  new Peon(color);
			}else{
				board[i][j] = new Piece(color);
			}
		}
	}
	return board;
}

void destroyBoard(Piece*** board){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			delete board[i][j];
		}
	}

	for (int i = 0; i < 8; ++i){
		delete[] board[i];
	}

	delete[] board;
}

void Mover(Piece*** board, Position* init, Position* end){
	int initX = init -> getX();
	int initY = init -> getY();
	int endX = end -> getX();
	int endY = end -> getY();
	if((board[initX][initY] -> getType() != VACIA) && (board[endX][endY] -> getType() == VACIA || board[endX][endY] -> getColor() != board[initX][initY] -> getColor())){
		board[endX][endY] = board[initX][initY];
		board[initX][initY] = new Piece((board[initX][initY]) -> getColor());
	}	
}

bool isSomethingInMiddle(Piece*** board, Position* init, Position* end){
	int initX = init -> getX();
	int initY = init -> getY();
	int endX = end -> getX();
	int endY = end -> getY();
	if(board[initX][initY] -> getType() == TORRE){
		if(endY > initY){ // se mueve a la derecha.
			for (int i = endY - 1; i > initY; --i){
				if(board[initX][i] -> getType() != VACIA){
					return true;
				}
			}
			return false;
		}else if(initY > endY){ // se mueve a la izquierda.
			for (int i = endY + 1; i < initY; ++i){
				if(board[initX][i] -> getType() != VACIA){
					return true;
				}
			}
			return false;
		}else if(endX > initX){ // se mueve a abajo.
			for (int i = endX - 1; i > initX; --i){
				if(board[i][initY] -> getType() != VACIA){
					return true;
				}
			}
			return false;
		}else if(initX > endX){ // se mueve a la arriba.
			for (int i = endX + 1 ; i < initX; ++i){
				if(board[i][initY] -> getType() != VACIA){
					return true;
				}
			}
			return false;
		}
	}else if(board[initX][initY] -> getType() == PEON){
		return board[endX][endY] -> getType() != VACIA;
	}else{
		return false;
	}
}