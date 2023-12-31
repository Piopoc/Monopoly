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
        Cell whereIs(Player p);
        bool beyondStart(Player p, Cell from, Cell to);
        ~tabellone(){};
    private:
        std::vector<std::shared_ptr<Cell>> tabs;
        int parametrizzazione_bordo_x(int t);
        int parametrizzazione_bordo_y(int t);
        std::string create_coordinates(int t);
};

#endif