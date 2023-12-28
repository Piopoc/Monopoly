#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player{
    public:
    //costruttore con id player
        Player(int ID);
    //controllo se giocatore ha denaro
        bool hasMoney();
    //ottiene il saldo giocatore
        int saldo();
    //versa una somma di denaro al giocatore
        void versa(int x);
    //preleva una somma di denaro al giocatore, se non c'è disponibilità lancia eccezione, si presuppone che nel main venga controllato prima se c'è disponibilità per non gestire in try catch
        void preleva(int x);
    //ottieni id del giocatore
        int getID();
    private:
    //fiorini
        int cash;
    //id del giocatore
        int playerID;

};
//lancia 2 dadi e ottieni somma
int dadi();
#endif