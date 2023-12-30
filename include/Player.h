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
    //controllo se ha abbastanza denaro da spendere
        bool hasThisMoney(int valore);
    //ottiene il saldo giocatore
        int saldo();
    //versa una somma di denaro al giocatore
        void versa(int x);
    //preleva una somma di denaro al giocatore, se non c'è disponibilità lancia eccezione, si presuppone che nel main venga controllato prima se c'è disponibilità per non gestire in try catch
        void preleva(int x);
    //ottieni id del giocatore
        int getID() const;
    //controlla se puo e sceglie se comprare p=25% computer
        bool computerCompra(int valore);
    private:
    //fiorini
        int cash;
    //id del giocatore
        int playerID;
};
int dadi();
bool noMaxRipetuti(vector<int> a);
int getPosMax(vector<int> a);
void rilanciaMaxRipetuti(vector<int> a);

#endif