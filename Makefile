main: main.o Position.o
	g++ main.o Position.o -o Chess.exe
	
main.o:	main.cpp Position.h
	g++ -c main.cpp 

Position.o:	Position.cpp Position.h
	g++ -c Position.cpp 

clean:	
	rm *.o  Chess.exe