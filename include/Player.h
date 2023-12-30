#ifndef PLAYER_H
#define PLAYER_H

class Player{
    public:
    //costruttore con id player
        explicit Player(int ID = 0);
    //assegnamento per copia
        Player& operator=(Player& p);
    //controllo se giocatore ha denaro
        bool hasMoney() const;
    //ottiene il saldo giocatore
        int saldo();
    //versa una somma di denaro al giocatore
        void versa(int x);
    //preleva una somma di denaro al giocatore, se non c'è disponibilità lancia eccezione, si presuppone che nel main venga controllato prima se c'è disponibilità per non gestire in try catch
        void preleva(int x);
    //ottieni id del giocatore
        int getID() const;
    private:
    //fiorini
        int cash;
    //id del giocatore
        int playerID;

};
int dadi();

#endif