main: main.o Position.o Piece.o Alfil.o Caballo.o Dama.o Peon.o Rey.o Torre.o
	g++ main.o Position.o  Piece.o  Alfil.o  Caballo.o Dama.o Peon.o  Rey.o Torre.o -o  Chess.exe -lmenu -lpanel -lncurses
	
	
main.o:	main.cpp Position.h 
	g++ -c main.cpp 

Position.o:	Position.cpp Position.h
	g++ -c Position.cpp 

Piece.o: Piece.cpp Piece.h Enum.h
	g++ -c Piece.cpp

Alfil.o: Alfil.cpp Alfil.h 
	g++ -c Alfil.cpp

Caballo.o: Caballo.cpp Caballo.h 
	g++ -c Caballo.cpp

Dama.o: Dama.cpp Dama.h
	g++ -c Dama.cpp

Peon.o: Peon.cpp Peon.h
	g++ -c Peon.cpp

Rey.o: Rey.cpp Rey.h
	g++ -c Rey.cpp

Torre.o: Torre.cpp Torre.h
	g++ -c Torre.cpp




clean:	
	rm *.o  Chess.exe
	clear

execute:
	./Chess.exe
	