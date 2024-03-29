// @author Alberto Levorato, matricola: 2066600

#include <iostream>

#include "../include/Player.h"

//costruttore
Player::Player(int ID)
    : cash{100}, playerID{ID}, currentPos{0}
{
    if(ID<1 || ID>4){
        throw std::logic_error{"ID compresi tra 1 e 4"};
    }
}
//funzioni membro
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
    if(cash-x<0){
        throw std::logic_error{"Denaro insufficiente per prelevare"};
    }
    cash -= x;
}
int Player::get_ID() const
{
    return playerID;
}
bool Player::has_this_money(int value)
{
    return (cash - value) >= 0;
}
bool Player::pc_buys(int value)
{
    if(has_this_money(value)){
        srand (time(NULL));
        return (rand() % 4 + 1)==1;
    }
    return false;
}
int Player::get_currpos() const{
    return currentPos;
}
void Player::set_currpos(int pos){
    if(pos<0 || pos>27){
        throw std::logic_error{"Posizione non valida"};
    }
    currentPos = pos;
}
//helper function
int dice()
{
    rand ();
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}