#ifndef __MOH_H
#define __MOH_H

class Player
{
    int x,y,d,radius,wall;
    bool turn;
public:
        bool getTurn();
        void Chg();
        int getX();
        int getY();
	int getDestination();
	int getRadius();
	int getWall();
	void countWall();
	void setX(int x);
	void setY(int y);
	Player(int x,int y,int d, int radius, bool turn, int wall): x(x), y(y), d(d), radius(radius), turn(turn), wall(wall)
    {}
};
#endif

