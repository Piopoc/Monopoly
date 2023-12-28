// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include "../include/Player.h"

Player::Player(int ID)
    : cash = 100, playerID = x; 
{
}
bool Player::hasMoney()
{
    return cash == 0;
}
int Player::saldo()
{
    return cash;
}
void Player::versa(int x)
{
    cash += x;
}
void Player::preleva(int x)
{
    if(cash-x<0) throw std::exception();
    cash -= x;
}
int Player::getID()
{
    return playerID;
}
int dadi()
{
    srand (time(NULL));
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}
