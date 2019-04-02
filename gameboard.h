#ifndef __gameboard_H
#define __gameboard_H
#include"moh.h"
#include<SDL/SDL.h>
#include<SDL/SDL_gfxPrimitives.h>
#include<iostream>
#include<string>
using namespace std;

struct coor{int x,y;};	
class Gameboard
{
    
	int abmr(bool [17][17], int, int, int, char);
	int check(int,int,int);
	int **a;
        int w,h;
	Player *p1, *p2;
	SDL_Surface* screen;
	void draw();
	Player* tU();
	Player* notU();
	void put(int,int);
public:
    Gameboard();
	coor sps(int, int);
	void generate();
	void act(int, int);
	bool end();
};

#endif

