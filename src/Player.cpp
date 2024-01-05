// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include <queue>
#include "../include/Cell.h"
#include "../include/Player.h"

Player::Player(int ID)
    : cash{100}, playerID{ID}, currentPos(0)
{
    if(ID<1 || ID>4){
        throw std::logic_error{"ID compresi tra 1 e 4"};
    }
}
Player& Player::operator=(Player& p)
{
    cash = p.cash;
    playerID = p.playerID;
    return *this;
}
int Player::get_money()
{
    return cash;
}
void Player::deposit(int x)
{
    cash += x;
}
void Player::withdraw(int x)
{
    if(cash-x<0) throw std::exception();
    cash -= x;
}
int Player::get_ID() const
{
    return playerID;
}
bool Player::has_this_money(int valore)
{
    return (cash - valore) > 0;
}
bool Player::pc_buys(int valore)
{
    if(has_this_money(valore)){
        srand (time(NULL));
        return (rand() % 4 + 1)==1;
    }
    return false;
}
int Player::get_currpos() const{
    return currentPos;
}
void Player::set_currpos(int pos){
    currentPos = pos;
}

int dice()
{
    rand ();
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}