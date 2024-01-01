// @author Alberto Levorato, matricola: 2066600

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

class Cell;

class Player{
    public:
    //costruttore con id player
        explicit Player(int ID = 0);
    //assegnamento per copia
        Player& operator=(Player& p);
    //controllo se ha abbastanza denaro da spendere
        bool has_this_money(int valore);
    //ottiene il saldo giocatore
        int get_money();
    //versa una somma di denaro al giocatore
        void deposit(int x);
    //preleva una somma di denaro al giocatore, se non c'è disponibilità lancia eccezione, si presuppone che nel main venga controllato prima se c'è disponibilità per non gestire in try catch
        void withdraw(int x);
    //ottieni id del giocatore
        int get_ID() const;
    //controlla se puo e sceglie se comprare p=25% computer
        bool pc_buys(int valore);
    //dove si trova
        Cell get_currCell() const;
    //dove va
        void set_currCell(Cell curr);
    private:
    //fiorini
        int cash;
    //id del giocatore
        int playerID;
    //cella in cui si trova
        Cell* currentCell;
};
//tira 2 dadi
int dice();
//controlla se il lancio più alto ha un pareggio
bool repeated_max(std::vector<int> a);
//ottiene posizione del giocatore con punteggio massimo all'interno dell'array
int get_posmax(std::vector<int> a);
//rilancia i dadi massimi in pareggio
void throw_again(std::vector<int> a);

#endif