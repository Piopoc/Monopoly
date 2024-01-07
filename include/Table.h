#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include "../include/Cell.h"

class Table{
    public:
        Table(); // costruttore
        void print_matrix(); // stampa il tabellone tramite il caricamento degli elementi in una "matrice"
        std::shared_ptr<Cell> get_cell(int pos); // restituisce la ref alla cell dell'indice array
        void start_game(Player* p1, Player* p2, Player* p3, Player* p4); // giocatori sulla casella di partenza
        bool beyond_start(Player* p, int from); // verifica se player passa per casella con P
        void move(Player* p, int spostamenti); // spostamento del player da posizione attuale a posizione indicata da lancio dei dadi
        std::string get_cellname(int pos); // ritorna casella stile scacchiera o campo di battaglia navale
        void elimination(Player* p); // elimina tutte le proprietà
        void list_property(std::queue<Player*>& pList, Player* pt); // mostra le proprietà di ogni giocatore ancora in gioco
        void bank_account(std::queue<Player*>& pList, Player* pt); // mostra quanti fiorini possiedono i giocatori che non sono stati eliminati
        ~Table(){}; // distruttore
    private:
        std::vector<std::shared_ptr<Cell>> tabs;
        int parametrizzazione_bordo_x(int t);
        int parametrizzazione_bordo_y(int t);
};

#endif