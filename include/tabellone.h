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
        std::vector<Cell> tabs;
};

#endif