// @author Alberto Levorato, matricola: 2066600

#ifndef PLAYER_H
#define PLAYER_H

class Player{
    public:
        explicit Player(int ID); //costruttore con id player
        Player& operator=(Player& p); //assegnamento per copia
        bool has_this_money(int valore); //controllo se ha abbastanza denaro da spendere
        int get_money(); //ottiene il saldo giocatore
        void deposit(int x); //versa una somma di denaro al giocatore
        void withdraw(int x); //preleva una somma di denaro al giocatore, se non c'è disponibilità lancia eccezione, si presuppone che nel main venga controllato prima se c'è disponibilità per non gestire in try catch
        int get_ID() const; //ottieni id del giocatore  
        bool pc_buys(int valore); //controlla se puo e sceglie se comprare p=25% computer
        int get_currpos() const; //dove si trova nel vector
        void set_currpos(int pos); //dove va
    private:
        int cash; //fiorini
        int playerID; //id del giocatore
        int currentPos; //cella in cui si trova
};
int dice(); //tira 2 dadi

#endif