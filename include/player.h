#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class player{
    public:
        player();
        bool hasMoney();
        int saldo();
        void versa(int x);
        void preleva(int x);
        void setID(int x);
        int getID();
    private:
        int cash;
        bool belongTo; // ??
        int playerID;

};
int dadi();
#endif