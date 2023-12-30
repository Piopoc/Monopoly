// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include "../include/Player.h"

Player::Player(int ID)
    : cash{100}, playerID{ID} 
{
}
Player& Player::operator=(Player& p)
{
    cash = p.cash;
    playerID = p.playerID;
    return *this;
}
bool Player::hasMoney() const
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
int Player::getID() const
{
    return playerID;
}

int dadi() //va messo il seed???????????????????????????????? se vuoi che ogni volta estragga gli stessi valori
{
    srand (time(NULL));
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}
