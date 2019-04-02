#include<iostream>
#include<SDL/SDL.h>
#include<SDL/SDL_gfxPrimitives.h>
#include"gameboard.h"
#include"moh.h"
using namespace std;

int main()
{
	Gameboard* gb = new Gameboard();
	gb->generate();
	SDL_Event event;
	coor b;
	while(!gb->end())
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {   b.x = gb->sps(event.button.x,event.button.y).x;
				b.y = gb->sps(event.button.x,event.button.y).y;    
				gb->act(b.x,b.y);
            }
            gb->generate();
        }    
    }    
}
