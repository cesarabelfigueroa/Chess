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
bool isValiEntry(string move);
Position* createPosition(char, char);
int valueOfChar(char);
Piece*** createBoard();
void showBoard(Piece***);

int main(int argc, char *argv[]){
 	Piece*** board = createBoard();
	initscr();	
	start_color();
	init_pair(1, COLOR_BLACK, 0);
	init_pair(2, COLOR_WHITE, 0);
	showBoard(board);
	getch();	
	endwin();			
	return 0;
}

void showBoard(Piece*** board){
	printw("\n\n");
	printw("\t A \t B \t C \t D \t E \t F \t G \t H \t\n\n\n");
	for( int i = 0; i < 8; i++ ){
		addch(i + 48);
		printw("\t");
		for (int j = 0; j < 8; ++j){
			printw("[");
			attron( COLOR_PAIR(board[i][j] -> getColor() + 1) | A_BOLD );
			addch(board[i][j] -> toString());
			attroff(COLOR_PAIR(board[i][j] -> getColor() + 1));
			printw("]");
			printw("\t");
		}
		printw("\n\n\n");
	}
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