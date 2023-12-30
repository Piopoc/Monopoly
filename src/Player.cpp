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
bool hasThisMoney(int valore)
{
    return (cash - valore) > 0;
}
bool computerCompra(int valore) //va messo il seed???????????????????????????????? se vuoi che ogni volta estragga gli stessi valori
{
    if(hasThisMoney(valore)){
        srand (time(NULL));
        return (rand() % 4 + 1)==1;
    }
    return false
}

int dadi() //va messo il seed???????????????????????????????? se vuoi che ogni volta estragga gli stessi valori
{
    srand (time(NULL));
    return (rand() % 6 + 1)+(rand() % 6 + 1);
}
bool noMaxRipetuti(vector<int> a){
        int max = 0;
        bool done = false
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
int getPosMax(vector<int> a){
    int max = 0;
    for(int i = 1; i<4; i++){
        if(a[i]>a[max]){
            max = i;
        }
    }
    return max;
}
void rilanciaMaxRipetuti(vector<int> a){
    for(int i = 0; i<4; i++){
        if(a[i]==-1){
            a[i] = dadi();
        }
    }
}