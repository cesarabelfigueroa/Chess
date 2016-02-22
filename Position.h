#ifndef POSITION_H
#define POSITION_H

class Position{
private:
	int x,y;

public:
	Position(int, int);
	~Position();
	int getX();
	void setX(int);
	int getY();
	void setY(int);
};

#endif