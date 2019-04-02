#include "moh.h"

bool Player::getTurn()
{
    return turn;
}

void Player::Chg()
{
    turn = !turn;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}
int Player::getDestination()
{
	return d;
}
int Player::getRadius()
{
	return radius;
}
int Player::getWall()
{
	return wall;
}
void Player::countWall()
{
	wall--;
}
void Player::setX(int x)
{
	this->x = x;
}

void Player::setY(int y)
{
	this->y = y;
} 



