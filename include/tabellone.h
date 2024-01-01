#ifndef TABELLONE_H
#define TABELLONE_H

#include <iostream>
#include <vector>
#include <memory>
#include "../include/Cell.h"

class tabellone{
    public:
        tabellone();
        void stampa();
        Cell* get_cell(int pos); //da definire che torna la refalla cell dell'indice arrray
        bool beyond_start(Player* p, int from, int to); //da definire
        void move(Player* p, int spostamenti); //da definire
        std::string get_cellname(int pos); //ritorna ad es A1
        void elimination(Player* p); // elimina tutte le proprietà
        ~tabellone(){};
    private:
        std::vector<std::shared_ptr<Cell>> tabs; //non basterebbe fare vector<Cell*>
        int parametrizzazione_bordo_x(int t); //serve?
        int parametrizzazione_bordo_y(int t); //serve?
        std::string create_coordinates(int t); //non serve più?
};

#endif