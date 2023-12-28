#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class player{
    public:
        void move(int passi); // funzione di spostamento nel tabellone
        bool hasMoney();
        int saldo();
        void versa(int x);
        void preleva(int x);
    private:
        int cash;
        bool belongTo; // ??

};
int dadi();
#endif