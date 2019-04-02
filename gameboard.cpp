#include "gameboard.h"

Gameboard::Gameboard()
{
    a = new int*[17];
    for(int i = 0; i < 17; i ++)
    {
        a[i] = new int[17];
        for(int j = 0 ; j < 17; j ++)
            a[i][j] = 0;
    }
	a[8][0] = 2;
	a[8][16] = 1;
	p2 = new Player(8,0,16,20,false,10);
	p1 = new Player(8,16,0,20,true,10);
	draw();
}
void Gameboard::draw()
{
	h = 60;
	w = 14;
	SDL_Init(0);
    screen = SDL_SetVideoMode( (h * 9) + (w * 8), (h * 9) + (w * 8), 32, SDL_SWSURFACE );
}

void Gameboard::generate()
{
	boxRGBA(screen,0,0,(h * 9) + (w * 8),(h * 9) + (w * 8),184,134,11,255);
	for(int i = 1; i < 9 ; i ++)
	{
		boxRGBA(screen, 0 , i*h + (i-1)*w , (h * 9) + (w * 8) , i*(h+w),218,165,32,255);
		boxRGBA(screen,i*h + (i-1)*w , 0 , i*(h+w) , (h * 9) + (w * 8),218,165,32,255);
	}
	filledCircleRGBA(screen,(p1->getX()/2)*(h+w)+h/2,(p1->getY()/2)*(h+w)+h/2,p1->getRadius(),0,206,209,252);
	filledCircleRGBA(screen,(p2->getX()/2)*(h+w)+h/2,(p2->getY()/2)*(h+w)+h/2,p2->getRadius(),255,69,0,252);
	for(int i = 1; i <= 15; i+=2)
        for(int j = 1 ; j <= 15; j+=2)
        {
			if((a[i-1][j] == 3) && (a[i][j] == 3) && (a[i+1][j] == 3))
				boxRGBA(screen,(h * (i/2 +1)) + (w * (i/2)) - h,(h * (j/2 +1)) + (w * (j/2)),(h * (i/2 +1)) + (w * (i/2)) + (h+w),(h * (j/2 +1)) + (w * (j/2)) + w,139,69,19,255);
			if((a[i][j-1] == 3) && (a[i][j] == 3) && (a[i][j+1] == 3))
				boxRGBA(screen,(h * (i/2 +1)) + (w * (i/2)),(h * (j/2 +1)) + (w * (j/2)) - h,(h * (i/2 +1)) + (w * (i/2)) + w,(h * (j/2 +1)) + (w * (j/2)) + (h+w),139,69,19,255);
		}	
	SDL_Flip(screen);
}
coor Gameboard::sps(int x, int y)
{
	coor a;
	a.x=-1;
	a.y=-1;
	for(int i = 0; i <= 8; i++)
    {
        for(int j = 0 ; j <= 8; j++)
        {
			if ( ( (x >= i*(h+w)) && (x <= (i*(h+w) +h)) ) && ( (y >= j*(h+w)) && (y <= (j*(h+w) +h)) ) )
			{	
				a.x=i*2;
				a.y=j*2;
				break;
			}
			else if ( ( (x >= (i*(h+w) + h)) && (x <= (i*(h+w) + (h+w) )) ) && ( (y >= (j*(h+w) + h)) && (y <= (j*(h+w) +(h+w))) ) );
			else if((( (y >= (j*(h+w) + h)) && (y <= (j*(h+w) +(h+w))) ))&&((x >= i*(h+w)) && (x <= (i*(h+w) +h))))
			{
				a.x=i*2;
				a.y=j*2+1;
				break;
			}
			else if(( ( (x >= (i*(h+w) + h)) && (x <= (i*(h+w) + (h+w) )) && ( (y >= j*(h+w)) && (y <= (j*(h+w) +h))))))
			{
				a.x=i*2+1;
				a.y=j*2;
				break;
			}
		}
    }
	return a;
}
int Gameboard::abmr(bool a_copy[17][17], int x, int y, int d, char mark1)
{
	int counter=0;
	int res;
	char mark2;
	int i,j;
	if (y==d) return 1;
	a_copy[x][y]=true;
	mark2=mark1;
	while (counter<4)
	{
		if (mark2=='t')
		{
			if ((y>0) && (a_copy[x][y-2]==false) && (a[x][y-1]==0))
			{
				res=abmr(a_copy,x,y-2,d,mark1);
				if (res>0)
				
					return res;
			}
			mark2='r';
			counter++;
		}
		else if (mark2=='r')
		{
			if ((x<17-1) && (a_copy[x+2][y]==false) && (a[x+1][y]==0))
			{
				res=abmr(a_copy,x+2,y,d,mark1);
				if (res>0) 	
					return res;	
			}
			mark2='b';
			counter++;
		}
		else if (mark2=='b')
		{
			if ((y<17-1) && (a_copy[x][y+2]==false) && (a[x][y+1]==0))
			{
				res=abmr(a_copy,x,y+2,d,mark1);
				if (res>0)
					return res;
			}
			mark2='l';
			counter++;
		}
		else if (mark2=='l')
		{
			if ((x>0) && (a_copy[x-2][y]==false) && (a[x-1][y]==0))
			{
				res=abmr(a_copy,x-2,y,d,mark1);
				if (res>0)
					return res;
			}
			mark2='t';
			counter++;
		}
	}		
	return 0; 
}

int Gameboard::check(int x, int y, int d)
{
	 bool a_copy[17][17];
	 int i,j;
	 for (i=0; i<17; i++) 
		for (j=0; j<17; j++) 
			a_copy[i][j]=false;
	 if (d==0)
		 i=abmr(a_copy, x, y, d, 't');
	 else i=abmr(a_copy, x, y, d, 'b');
	 return i;
}

bool Gameboard::end()
{
	if( (p1->getY() == p1->getDestination()) || (p2->getY() == p2->getDestination()) )
		 return true;
	return false;
}
Player* Gameboard::tU()
{
		if (p1->getTurn()) return p1;
		return p2;
}

Player* Gameboard::notU()
{
		if (!(p1->getTurn())) return p1;
		return p2;
}
void Gameboard::put(int x,int y)
{
	Player* bx=tU();
	Player* by=notU();
	if ( (by->getX() == x) && (by->getY() == y) ) return;
	a[x][y] = a[bx->getX()][bx->getY()];
	a[bx->getX()][bx->getY()]= 0 ;
	bx->setX(x);
	bx->setY(y);
	bx->Chg();
	by->Chg();
}
void Gameboard::act(int x , int y)
{
    int t=0;
    if((x == -1)||((tU()->getX() == x) && (tU()->getY() == y))) return;
	if ((x % 2 == 0)&&(y %2 == 0))
	{
		if( ( (x == tU()->getX()+2) && (y == tU()->getY()) ) && (a[tU()->getX()+1][tU()->getY()] == 0))	
			put(x,y);
		else if (( (x == tU()->getX()-2) && (y == tU()->getY()) ) && (a[tU()->getX()-1][tU()->getY()] == 0))   put(x,y);
		else if (( (y == tU()->getY()+2) && (x == tU()->getX()) ) && (a[tU()->getX()][tU()->getY()+1] == 0))   put(x,y);
		else if (( (y == tU()->getY()-2) && (x == tU()->getX()) ) && (a[tU()->getX()][tU()->getY()-1] == 0))   put(x,y);
	else if((x==notU()->getX()+2) && (y==notU()->getY()) && (tU()->getX()==notU()->getX()-2) && ( tU()->getY() == notU()->getY()) )	
	if ((a[tU()->getX()+1][tU()->getY()] == 0)&&(a[tU()->getX()+3][tU()->getY()] == 0))   put(x,y);
	else if( (x == notU()->getX()-2) && (y == notU()->getY()) && (tU()->getX() == notU()->getX()+2) && ( tU()->getY() == notU()->getY()) )
			
		if ((a[tU()->getX()-1][tU()->getY()] == 0)&&(a[tU()->getX()-3][tU()->getY()] == 0))   put(x,y);
	else if( (y == notU()->getY()+2) && (x == notU()->getX()) && (tU()->getY() == notU()->getY()-2) && ( tU()->getX() == notU()->getX()) )
			
		if ((a[tU()->getX()][tU()->getY()+1] == 0)&&(a[tU()->getX()][tU()->getY()+3] == 0))  put(x,y);
	else if( (y == notU()->getY()-2) && (x == notU()->getX()) && (tU()->getY() == notU()->getY()+2) && ( tU()->getX() == notU()->getX()) )
			
		if ((a[tU()->getX()][tU()->getY()-1] == 0)&&(a[tU()->getX()][tU()->getY()-3] == 0))  put(x,y);
	else if( (x == notU()->getX()) && (y == notU()->getY()+2) && (tU()->getX() == notU()->getX()-2) && ( tU()->getY() == notU()->getY()) )
		if (a[notU()->getX()][notU()->getY()+1] == 3) return;
	else if (notU()->getX() == 16)  put(x,y);
	else if (tU()->getX()+3>16) return;
	else if (a[tU()->getX()+3][tU()->getY()] == 3)  put(x,y);
	}
	else if( (x == notU()->getX()) && (y == notU()->getY()-2) && (tU()->getX() == notU()->getX()-2) && ( tU()->getY() == notU()->getY()) )
		{	
			if (a[notU()->getX()][notU()->getY()-1] == 3) return;
			else if (notU()->getX() == 16)  put(x,y);
			else if (tU()->getX()+3>16) return;
			else if (a[tU()->getX()+3][tU()->getY()] == 3)  put(x,y);
		}
	else if( (x == notU()->getX()) && (y == notU()->getY()+2) && (tU()->getX() == notU()->getX()+2) && ( tU()->getY() == notU()->getY()) )
		{	
			if (a[notU()->getX()][notU()->getY()+1] == 3) return;
			else if (notU()->getX() == 0)   put(x,y);
			else if (tU()->getX()-3<0) return;
			else if ((a[tU()->getX()-3][tU()->getY()] == 3))  put(x,y);
		}		
	else if( (x == notU()->getX()) && (y == notU()->getY()-2) && (tU()->getX() == notU()->getX()+2) && ( tU()->getY() == notU()->getY()) )
		{	
			if (a[notU()->getX()][notU()->getY()-1] == 3) return;
			else if (notU()->getX() == 0)  put(x,y);
			else if (tU()->getX()-3<0) return;
			else if ((a[tU()->getX()-3][tU()->getY()] == 3)) put(x,y);
		}
	else if( (y == notU()->getY()) && (x == notU()->getX()+2) && (tU()->getY() == notU()->getY()-2) && ( tU()->getX() == notU()->getX()) )
		{	
			if (a[notU()->getX()+1][notU()->getY()] == 3) return;
			else if (notU()->getY() == 16)  put(x,y);
			else if (tU()->getY()+3>16) return;
			else if ((a[tU()->getX()][tU()->getY()+3] == 3))  put(x,y);
		}
	else if( (y == notU()->getY()) && (x == notU()->getX()-2) && (tU()->getY() == notU()->getY()-2) && ( tU()->getX() == notU()->getX()) )
		{	
			if (a[notU()->getX()-1][notU()->getY()] == 3) return;
			else if (notU()->getY() == 16)  put(x,y);
			else if (tU()->getY()+3>16) return;
			else if ((a[tU()->getX()][tU()->getY()+3] == 3))   put(x,y);
		}
	else if( (y == notU()->getY()) && (x == notU()->getX()+2) && (tU()->getY() == notU()->getY()+2) && ( tU()->getX() == notU()->getX()) )
		{	
			if (a[notU()->getX()+1][notU()->getY()] == 3) return;
			else if (notU()->getY() == 0)   put(x,y);
			else if (tU()->getY()-3<0) return;
			else if ((a[tU()->getX()][tU()->getY()-3] == 3))   put(x,y);
		}
	else if( (y == notU()->getY()) && (x == notU()->getX()-2) && (tU()->getY() == notU()->getY()+2) && ( tU()->getX() == notU()->getX()) )
		{	
			if (a[notU()->getX()-1][notU()->getY()] == 3) return;
			else if (notU()->getY() == 0)  put(x,y);
			else if (tU()->getY()-3<0) return;
			else if ((a[tU()->getX()][tU()->getY()-3] == 3))   put(x,y);
		}	
	else 
	{
		Player* bx=tU();
		Player* by=notU();
		if ((y % 2 == 1)&&(x<15))
		{
			if((a[x][y] == 0)&&(a[x+1][y] == 0)&&(a[x+2][y] == 0))
			{
				if (bx->getWall() == 0) return;
				cout << " for this player" << " : "<< bx->getWall()-1 << "Walls Remaining" << endl;

				a[x][y]=3;
				a[x+1][y]=3;
				a[x+2][y]=3;
				int l=check(bx->getX(), bx->getY(), bx->getDestination())+check(by->getX(), by->getY(), by->getDestination());
				if (l != 2)
				{
					a[x][y]=0;
					a[x+1][y]=0;
					a[x+2][y]=0;
					return;
				}
				bx->countWall();
				bx->Chg();
				by->Chg();
			}	
		}
		else if ((x % 2 == 1)&&(y<15))
		{
			if((a[x][y] == 0)&&(a[x][y+1] == 0)&&(a[x][y+2] == 0))
			{
				if (bx->getWall() == 0) return;
				cout << " for this player" << " : "<< bx->getWall()-1 << "Walls Remaining" << endl;
				a[x][y]=3;
				a[x][y+1]=3;
				a[x][y+2]=3;
				int l=check(bx->getX(), bx->getY(), bx->getDestination())+check(by->getX(), by->getY(), by->getDestination());
				if (l != 2)
				{
					a[x][y]=0;
					a[x][y+1]=0;
					a[x][y+2]=0;
					return;
				};
				bx->countWall();
				bx->Chg();
				by->Chg();
			}	
		}	
	}	
}
