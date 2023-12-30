#ifndef TABELLONE_H
#define TABELLONE_H

#include <iostream>
#include <vector>
#include "../include/Cell.h"

class tabellone{
    public:
        tabellone();
        void stampa();
    private:
        std::vector<Cell*> tabs;
        int parametrizzazione_bordo_x(int t);
        int parametrizzazione_bordo_y(int t);
        std::string create_coordinates(int t);
};

#endif