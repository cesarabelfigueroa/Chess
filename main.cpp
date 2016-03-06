/*---- Standard C++ directives ----*/
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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
using std::vector;
using std::iostream;
using std::fstream;
using std::ifstream;
using std::ofstream;

/*---- Functions Headers ----*/
bool isSameColor(Piece***, Position*, ENUM_COLOR);
bool isValiEntry(string);
Position* createPosition(char, char);
int valueOfChar(char);
Piece*** createBoard();
Piece*** createCopyBoard(Piece***);
void showBoard(Piece***);
void destroyBoard(Piece***);
bool Mover(Piece***, Position* , Position*);
bool isSomethingInMiddle(Piece***, Position*, Position*);
Position* placeToKing(Piece***, ENUM_COLOR);
Position* isCheck(Piece***, Position*);
vector<Position*> getTrailOfChequer(Piece***, Position*, Position*);
bool enemyChequer(Piece***, Position*);
bool isValidMove(Piece***, Position* init, Position* end);
bool isEmpty(Piece***, Position*);
bool isValidDestiny(Piece***, Position*, Position*);
bool isSameColor(Piece***, Position*, Position*);
bool isKing(Piece***, Position*);
bool isPeonEat(Piece*** , Position*, Position*);
bool cantMoveForScape(Piece***, Position*, Position*, ENUM_COLOR color);
bool cantEat(Piece***, Piece*);
bool cantMoveInMiddle(Piece***, Position*, Position*);
bool cantMoveKing(Piece***, Position*, ENUM_COLOR color);
Position* nexMoveHasCheck(Piece***, Position*, Position*, ENUM_COLOR);
void getEntry(int, char*);
void saveGame(Piece***);
bool uploadGame(Piece***);
void fillBoard(Piece***);

int main(int argc, char *argv[]){
 	Position* initial;
 	Position* end;
 	Position* king;
 	ENUM_COLOR color;
 	ENUM_COLOR enemyColor;
 	int x, y;
 	char* moves = new char[4];
 	int turn = 0;
 	bool hasMove = false;
 	bool playing = true;
	initscr();	
	start_color();
	init_pair(1, COLOR_BLACK, 0);
	init_pair(2, COLOR_WHITE, 0);
	init_pair(3, COLOR_BLACK, 0);
	clear();

	Piece*** board = createBoard();
	getmaxyx(stdscr,y,x);
	move(y/2,(x/2)-20);	
	attron(COLOR_PAIR(2));
	printw("Bienvenido a tu juego de ajedrez.");
	if(uploadGame(board)){
		move(1+y/2,(x/2)-20);
		printw("Su partida se cargo con éxito.");
	}else{
		move(1+y/2,(x/2)-20);
		printw("Su partida no se cargo con éxito, volvamos a jugar.");
		fillBoard(board);
	}
	attroff(COLOR_PAIR(2));
	getch();
	while(playing){
		clear();
		showBoard(board);
		if(turn%2 == 0){
			color = BLANCO;
		}else{
			color = NEGRO;
		}
		printw("\t1. Mover. \n");
		printw("\t2. Guardar Partida. \n");
		printw("\t3. Salir. \n\n");
		printw("\tAcción: ");
		noecho();
		hasMove = false;
		int choose = getch();
		if(choose == 49){
			clear();
			showBoard(board);
			getEntry(turn, moves);
			initial = createPosition(moves[1], moves[0]);
			end = createPosition(moves[3], moves[2]);
			king = placeToKing(board, color);
			Position* checkr = isCheck(board, king);
			bool nexMoveDanger = nexMoveHasCheck(board, initial, end, color); 
			if(isValiEntry(moves) && isSameColor(board, initial, color)){
				if(!nexMoveDanger && !checkr){
					if(Mover(board, initial , end)){
						turn++;
					}
				}else if(checkr && !nexMoveHasCheck){
					if(Mover(board, initial , end)){
						turn++;
					}
				}else if(checkr && nexMoveDanger){
					if(cantMoveForScape(board, checkr, king, color)){
						while(nexMoveDanger){
							delete initial;
							delete end;
							delete king;
							delete checkr;
							clear();
							showBoard(board);
							getEntry(turn, moves);
							initial = createPosition(moves[1], moves[0]);
							end = createPosition(moves[3], moves[2]);
							king = placeToKing(board, color);
							checkr = isCheck(board, king);
							nexMoveDanger = nexMoveHasCheck(board, initial, end, color); 
							if(!nexMoveHasCheck && isValiEntry(moves) && isSameColor(board, initial, color)){
								Mover(board, initial, end);
							}
						}
						turn++;
						getch();
					}else{
						clear();
						showBoard(board);
						printw("\n\tGracias por jugar.");
						if(color == NEGRO){
							printw("\n\tGanan las blancas.");
						}else{
							printw("\n\tGanan las negras.");
						}
						playing = false;
						getch();
					}
				}
			}
		}else if(choose == 50){
			saveGame(board);
			getch();
		}else if(choose == 51){
			clear();
			showBoard(board);
			printw("\n\tGracias por jugar.");
			getch();
			playing = false;
		}
		clear();
	}	
	destroyBoard(board);
	delete moves;
	delete initial;
	delete king;
	delete end;
	endwin();			
	return 0;
}


void  getEntry(int turn, char* move){
	ENUM_COLOR color;
	if(turn % 2){
		printw("\tTurno de las negras. \n\n");
		color = NEGRO;
	}else{
		printw("\tTurno de las blancas. \n\n");
		color = BLANCO;
	}
	printw("\tMovimiento: ");
	char value = getch();
	while(!(((int) value >= 65 && (int) value <= 72) ||((value >= 97)&& (value <= 104)))){
		value = getch();
	}
	move[0] = value;
	addch(value);
	value = getch();
	while(!(((int) value >= 48 && (int) value <= 55))){
		value = getch();
	}
	move[1] = value;
	addch(value);
	while(!(((int) value >= 65 && (int) value <= 72) ||((value >= 97)&& (value <= 104)))){
		value = getch();
	}
	move[2] = value;
	addch(value);
	value = getch();
	while(!(((int) value >= 48 && (int) value <= 55))){
		value = getch();
	}
	move[3] = value;
	addch(value);
}

bool isSameColor(Piece*** board, Position* initial, ENUM_COLOR color){
	return board[initial->getX()][initial->getY()] -> getColor() == color;
}

void showBoard(Piece*** board){
	printw("\n\n");
	printw("\t\t A \t B \t C \t D \t E \t F \t G \t H \t\n\n\n");
	for( int i = 0; i < 8; i++ ){
		printw("\t");
		addch(i + 48);
		printw("\t");
		for (int j = 0; j < 8; ++j){
			attron(COLOR_PAIR(board[i][j] -> getColor() + 1) | A_BOLD );
			if(board[i][j]){
				printw("[");
				if(board[i][j] -> getType() != VACIA){
					addch(board[i][j] -> toString());
				}else{
					addch(' ');
				}
				printw("]");
			}else{
				printw("[");
				addch(' ');
				printw("]");
			}
			attroff(COLOR_PAIR(board[i][j] -> getColor() + 1));
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

Position* nexMoveHasCheck(Piece*** board, Position* init, Position* end, ENUM_COLOR color){
	Piece*** copyBoard = createCopyBoard(board);
	Position* king = placeToKing(board, color); 
	if(Mover(copyBoard, init, end)){
		return isCheck(copyBoard,king);
	}else{
		delete king;
		return NULL;
	}
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


void fillBoard(Piece*** board){
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
}

Piece*** createBoard(){
	Piece*** board = new Piece**[8];
	for (int i = 0; i < 8; ++i){
		board[i] = new Piece*[8];
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

bool Mover(Piece*** board, Position* init, Position* end){
	int initX = init -> getX();
	int initY = init -> getY();
	int endX = end -> getX();
	int endY = end -> getY();
	if(isValidMove(board, init, end) && !isKing(board, end)){
		if(board[initX][initY] -> getType() == PEON && endX == 0 || endX == 7){
			board[endX][endY] = new Dama(board[initX][initY] -> getColor());
		}else{
			board[endX][endY] = board[initX][initY];
		}
		board[initX][initY] = new Piece((board[initX][initY]) -> getColor());
		return true;
	}
	return false;
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
		return board[endX][endY] -> getType() != VACIA && !isPeonEat(board, init, end);
	}else if(board[initX][initY] -> getType() == CABALLO){
		return false;
	}else if(board[initX][initY] -> getType() == ALFIL){
		if(initX + initY == endX + endY){
			if(endX < initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX + 1 ; i < initX; ++i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY--;
				}
				return false;
			}else if(endX > initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX -1 ; i > initX ; --i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY++;
				}
				return false;
			}
		}else if(initX - initY == endX - endY){
			if(endX < initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX + 1; i < initX; ++i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY++;
				}
				return false;
			}else if(endX > initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX - 1  ; i > initX ; --i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY--;
				}
				return false;
			}
		}
	}else if(board[initX][initY] -> getType() == REY){
		return false;
	}else if(board[initX][initY] -> getType() == DAMA){
		if(initX + initY == endX + endY){
			if(endX < initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX + 1 ; i < initX; ++i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY--;
				}
				return false;
			}else if(endX > initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX -1 ; i > initX ; --i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY++;
				}
				return false;
			}
		}else if(initX - initY == endX - endY){
			if(endX < initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX + 1; i < initX; ++i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY++;
				}
				return false;
			}else if(endX > initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX - 1  ; i > initX ; --i){
					if(board[i][referencesY] -> getType() != VACIA){
						return true;
					}
					referencesY--;
				}
				return false;
			}
		}if(endY > initY){ // se mueve a la derecha.
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
	}
	else{
		return false;
	}
}

Position* placeToKing(Piece*** board, ENUM_COLOR color){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if(board[i][j] -> getType() == REY && board[i][j] -> getColor() == color){
				Position* pos = new Position(i, j);
				return pos;
			}
		}
	}
}

Position* isCheck(Piece*** board, Position* king){
	Position* tempPosition = new Position(0, 0);
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			tempPosition -> setY(j);
			tempPosition -> setX(i);
			if(isValidMove(board, tempPosition, king)){
				return tempPosition;
			}
		}
	}
	delete tempPosition;
	return NULL;
}

bool enemyChequer(Piece*** board, Position* checkr){
	if(checkr){
		for (int i = 0; i < 8; ++i){
			for (int j = 0; j < 8; ++j){
				Position* init = new Position(i, j);
				if(isValidMove(board, init, checkr)){
					delete init;
					return true;
				}
				delete init;
			}
		}
		return false;
	}else{
		return false;
	}
}

bool isValidMove(Piece*** board, Position* init, Position* end){
	int initX = init -> getX();
	int initY = init -> getY();
	int endX = end -> getX();
	int endY = end -> getY();
	if(endX < 0 || endX > 7 || endY < 0 || endY > 7 || initX < 0 || initX > 7 || initY < 0 || initY  > 7){
		return false;
	}
	bool empty =  !isEmpty(board, init);
	bool validDestiny  = isValidDestiny(board, init, end);
	bool move = board[initX][initY] -> isValidMove(init, end);
	bool peonEat = isPeonEat(board, init, end);
	return empty && validDestiny && (move || peonEat); 
}

bool isEmpty(Piece*** board, Position* init){
	int initX = init -> getX();
	int initY = init -> getY();
	return (board[initX][initY] -> getType() == VACIA);
}

bool isValidDestiny(Piece*** board , Position* init, Position* end){
	int endX = end -> getX();
	int endY = end -> getY();
	return (endX >= 0 && endY <=7) && (isEmpty(board, end) || !isSameColor(board, init, end)) && !isSomethingInMiddle(board, init, end);
}

bool isSameColor(Piece*** board, Position* init , Position* end){
	int initX = init -> getX();
	int initY = init -> getY();
	int endX = end -> getX();
	int endY = end -> getY();
	return board[endX][endY] -> getColor() == board[initX][initY] -> getColor();
}

Piece*** createCopyBoard(Piece*** board){
	Piece*** copyBoard = new Piece**[8];
	for (int i = 0; i < 8; ++i){
		copyBoard[i] = new Piece*[8];
	}
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			copyBoard[i][j] = board[i][j];
		}
	}
	return copyBoard;
}

bool isKing(Piece*** board, Position* end){
	int endX = end -> getX();
	int endY = end -> getY();
	return (board[endX][endY] -> getType() == REY);
}

bool isPeonEat(Piece*** board, Position* init, Position* end){
	int initX = init -> getX();
	int initY = init -> getY();
	int endX = end -> getX();
	int endY = end -> getY();
	if((board[initX][initY]) -> getType() == PEON){
		if((board[endX][endY]) -> getType() != VACIA){
			if((board[initX][initY]) -> getColor() == BLANCO){
				if(endX == initX - 1 && endY == initY + 1){
					return true;
				}else if(endX == initX - 1 && endY == initY - 1){
					return true;
				}else{
					return false;
				}
			}else if((board[initX][initY]) -> getColor() == NEGRO){
				if(endX == initX + 1 && endY == initY + 1){
					return true;
				}else if(endX == initX + 1 && endY == initY - 1){
					return true;
				}else{
					return false;
				}
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else{
		false;
	}
}

vector<Position*> getTrailOfChequer(Piece*** board,Position* chequer, Position* king){
	int initX = chequer -> getX();
	int initY = chequer -> getY();
	int endX = king -> getX();
	int endY = king -> getY();
	vector<Position*> TrailOfChequer;
	if(board[initX][initY] -> getType() == TORRE){
		if(endY > initY){ // se mueve a la derecha.
			for (int i = endY - 1; i > initY; --i){
				TrailOfChequer.push_back(new Position(initX,i));
			}
		}else if(initY > endY){ // se mueve a la izquierda.
			for (int i = endY + 1; i < initY; ++i){
				TrailOfChequer.push_back(new Position(initX,i));	
			}
		}else if(endX > initX){ // se mueve a abajo.
			for (int i = endX - 1; i > initX; --i){
				TrailOfChequer.push_back(new Position(i,initY));
			}
		}else if(initX > endX){ // se mueve a la arriba.
			for (int i = endX + 1 ; i < initX; ++i){
				TrailOfChequer.push_back(new Position(i,initY));
			}
		}
	}else if(board[initX][initY] -> getType() == ALFIL){
		if(initX + initY == endX + endY){
			if(endX < initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX + 1 ; i < initX; ++i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY--;
				}
			}else if(endX > initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX -1 ; i > initX ; --i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY++;
				}
			}
		}else if(initX - initY == endX - endY){
			if(endX < initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX + 1; i < initX; ++i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY++;
				}
			}else if(endX > initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX - 1  ; i > initX ; --i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY--;
				}
			}
		}
	}else if(board[initX][initY] -> getType() == DAMA){
		if(endY > initY){ // se mueve a la derecha.
			for (int i = endY - 1; i > initY; --i){
				TrailOfChequer.push_back(new Position(initX,i));
			}
		}else if(initY > endY){ // se mueve a la izquierda.
			for (int i = endY + 1; i < initY; ++i){
				TrailOfChequer.push_back(new Position(initX,i));	
			}
		}else if(endX > initX){ // se mueve a abajo.
			for (int i = endX - 1; i > initX; --i){
				TrailOfChequer.push_back(new Position(i,initY));
			}
		}else if(initX > endX){ // se mueve a la arriba.
			for (int i = endX + 1 ; i < initX; ++i){
				TrailOfChequer.push_back(new Position(i,initY));
			}
		}else if(initX + initY == endX + endY){
			if(endX < initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX + 1 ; i < initX; ++i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY--;
				}
			}else if(endX > initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX -1 ; i > initX ; --i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY++;
				}
			}
		}else if(initX - initY == endX - endY){
			if(endX < initX && endY < initY){
				int referencesY = endY + 1;
				for (int i = endX + 1; i < initX; ++i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY++;
				}
			}else if(endX > initX && endY > initY){
				int referencesY = endY - 1;
				for (int i = endX - 1  ; i > initX ; --i){
					TrailOfChequer.push_back(new Position(i,referencesY));
					referencesY--;
				}
			}
		}
	}
	return TrailOfChequer;
}

bool cantMoveForScape(Piece*** board, Position* chequer, Position* king, ENUM_COLOR color){
	if(chequer && king){
		bool cantMoveInFront = cantMoveInMiddle(board, chequer, king);
		bool cantEat = enemyChequer(board, chequer);
		bool moveKing = cantMoveKing(board, king, color);
		return cantMoveInFront || cantEat || moveKing;
	}else{
		return false;
	}
}

bool cantMoveInMiddle(Piece*** board, Position* chequer, Position* king){
	if(chequer && king){
		vector<Position*> TrailOfChequer = getTrailOfChequer(board, chequer, king);
		for (int i = 0; i < TrailOfChequer.size(); ++i){
			for (int x = 0; x < 8 ; ++x){
				for (int y = 0; y < 8 ; ++y){
					Position* init = new Position(x, y);
					if(isValidMove(board, init, TrailOfChequer.at(i))){
						delete init;
						return true;
					}
					delete init;
				}
			}
		}
		return false;
	}
	return false;
}

bool cantMoveKing(Piece*** board, Position* king, ENUM_COLOR color){
	for (int i = -1; i <= 1; ++i){
		for (int j = -1; j <= 1; ++j){
			Position* newPosition = new Position(i,j);
			if(isValidMove(board, king, newPosition) && !nexMoveHasCheck(board, king, newPosition, color)){
				delete newPosition;
				return true;
			}
			delete newPosition;
		}
	}
	return false;
}

void saveGame(Piece*** board){
	ofstream fs("game.txt");
	string piece; 
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			piece = "";
			ENUM_COLOR color =  board[i][j] -> getColor();
			ENUM_TYPE type =  board[i][j] -> getType();
			if(color == NEGRO){
				piece += "N,";
			}else if(color == BLANCO){
				piece += "B,";
			}else{
				piece += "S,";
			}
			piece += board[i][j] -> toString();
			piece += ",";
			piece += (char) i + 48;
			piece += ",";
			piece += (char) j + 48;
			piece += ";";
			fs << piece.c_str();
		}
	}
	fs.close();
}

bool uploadGame(Piece*** board){
	char buffer[2];
	ENUM_COLOR color;
	int x;
	int y;
	Piece* piece;
	ENUM_TYPE type;
	ifstream fe("game.txt"); 
	if(fe){
		while(!fe.eof()){
			fe.getline(buffer, 2, ',');
			if(!strcmp(buffer, (char*) "N")){
				color = NEGRO;
			}else if(!strcmp(buffer, (char*)"B")){
				color = BLANCO;
			}else{
				color = NULO;
			}
			fe.getline(buffer, 2, ',');
			if(!strcmp(buffer,  (char*) "T")){
				piece = new Torre(color);
			}else if(!strcmp(buffer,  (char*) "C")){
				piece = new Caballo(color);
			}else if(!strcmp(buffer,  (char*) "P")){
				piece = new Peon(color);
			}else if(!strcmp(buffer,  (char*) "A")){
				piece = new Alfil(color);
			}else if(!strcmp(buffer,   (char*) "D")){
				piece = new Dama(color);
			}else if(!strcmp(buffer,  (char*) "R")){
				piece = new Rey(color);
			}else if(!strcmp(buffer,  (char*) "V")){
				piece = new Piece(color);
			}
			fe.getline(buffer, 2, ',');
			x = atoi(buffer);
			fe.getline(buffer, 2, ';');
			y = atoi(buffer);
			board[x][y] = piece;
			if(x == 7 && y == 7){
				break;
			}
		}
		fe.close();
		return true;
	}else{
		fe.close();
		return false;
	}
}