#include <iostream>
#include "../include/player.h"

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
    if(deposito-x<0) throw std::exception();
    cash -= x;
}