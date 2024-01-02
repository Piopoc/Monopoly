#ifndef TABELLONE_H
#define TABELLONE_H

#include <iostream>
#include <vector>
#include <memory>
#include "../include/Cell.h"

class tabellone{
    public:
        tabellone();
        void print_matrix();
        void start_game(Player* p1, Player* p2, Player* p3, Player* p4);
        Cell* get_cell(int pos);
        bool beyond_start(Player* p, int from);
        void move(Player* p, int spostamenti);
        std::string get_cellname(int pos); //ritorna ad es A1
        void elimination(Player* p); // elimina tutte le proprietà
        ~tabellone(){};
    private:
        std::vector<std::shared_ptr<Cell>> tabs;
        std::string** charge_matrix();
        //void delete_matrix(std::string**matrix,int dim);
        int parametrizzazione_bordo_x(int t);
        int parametrizzazione_bordo_y(int t);
};

#endif