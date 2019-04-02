#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <cstdlib>
#include "gameboard.h"
using namespace std;
int main()
{
	int n,k,l;
	cout << " Enter The Number OF The Minister : " ;
	cin >> n;
	while (n<=3)
	{
		cout << " Enter The Number OF The Minister Again : " ;
		cin >> n;
	}
	gameboard *gb= new gameboard(n);
	srand(time(0));
	int o=1;
	while (o>0)
	{
		k= rand () %n;
		l= rand () %n;
		gb->swap(k,l,n);
		o=gb->done(n);
	}
	if (n<20)
	{
		cout << " The 0,1 Show : " << endl;
		gb->generate(n);
	}
	gb->show(n);
}
