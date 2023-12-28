// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include "../include/player.h"

player::player(int ID)
    : cash = 100, playerID = x; 
{
}
bool player::hasMoney()
{
    return cash == 0;
}
int player::saldo()
{
    return cash;
}
void player::versa(int x)
{
    cash += x;
}
void player::preleva(int x)
{
    if(cash-x<0) throw std::exception();
    cash -= x;
}
int dadi()
{
    srand (time(NULL));
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}
int getID()
{
    return playerID;
}