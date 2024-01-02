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
bool repeated_max(std::vector<int> a){
        int max = 0;
        bool done = false;
        for(int i = 0; i<4; i++){
            if(a[i]>max){
                max = a[i];
            }
            if(max!=0 && a[i]==max){
                if(done){
                    std::cout<<"doppione di"<<a[i]<<std::endl;
                    return true;
                }
                //done = true;
            }
        }
        return done;
    }
int get_posmax(std::vector<int> a){
    int max = 0;
    for(int i = 1; i<4; i++){
        if(a[i]>a[max]){
            max = i;
        }
    }
    return max;
}
void throw_again(std::vector<int> a){
    int max = a[get_posmax(a)];
    for(int i = 0; i<4; i++){
        if(max!=0 && a[i]==max){
            a[i] = dice();
        }
    }
}