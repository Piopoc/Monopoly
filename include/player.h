#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class player{
    public:
        virtual player(std::string numeroPlayer)=0; // costruttore che deve essere sovrascritto sia da CPU che humanPlayer --> virtuale da overloading
        void move(int passi); // funzione di spostamento nel tabellone
        bool hasMoney();
        int saldo();
        void versa(int x);
        void preleva(int x);
    private:
        int cash;
        bool belongTo; // ??

};

#endif