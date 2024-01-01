// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include <queue>
#include "../include/Cell.h"
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
bool Player::pc_buys(int valore) //va messo il seed???????????????????????????????? se vuoi che ogni volta estragga gli stessi valori
{
    if(has_this_money(valore)){
        srand (time(NULL));
        return (rand() % 4 + 1)==1;
    }
    return false;
}
int get_currpos() const{
    return currentPos;
}
void set_currpos(int pos){
    currentPos = pos;
}

int dadi() //va messo il seed???????????????????????????????? se vuoi che ogni volta estragga gli stessi valori
{
    srand (time(NULL));
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}
bool noMaxRipetuti(std::vector<int> a){
        int max = 0;
        bool done = false;
        for(int i = 0; i<4; i++){
            if(a[i]>max){
                max = a[i];
            }
            if(max!=0 && a[i]==max){
                a[i] = -1;
                done = true;
            }
        }
        return done;
    }
int getPosMax(std::vector<int> a){
    int max = 0;
    for(int i = 1; i<4; i++){
        if(a[i]>a[max]){
            max = i;
        }
    }
    return max;
}
void rilanciaMaxRipetuti(std::vector<int> a){
    for(int i = 0; i<4; i++){
        if(a[i]==-1){
            a[i] = dadi();
        }
    }
}