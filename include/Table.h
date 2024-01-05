#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include "../include/Cell.h"

class Table{
    public:
        Table();
        void print_matrix();
        std::shared_ptr<Cell> get_cell(int pos); //da definire che torna la ref alla cell dell'indice array
        void start_game(Player* p1, Player* p2, Player* p3, Player* p4);
        bool beyond_start(Player* p, int from); //da definire
        void move(Player* p, int spostamenti); //da definire
        std::string get_cellname(int pos); //ritorna ad es A1
        void elimination(Player* p); // elimina tutte le proprietà
        //void show(Player* p1, Player* p2, Player* p3, Player* p4);
        void list_property(std::queue<Player*>& pList);
        void bank_account(std::queue<Player*>& pList);
        ~Table(){};
    private:
        std::vector<std::shared_ptr<Cell>> tabs;
        int parametrizzazione_bordo_x(int t);
        int parametrizzazione_bordo_y(int t);
};

#endif
////
////
////