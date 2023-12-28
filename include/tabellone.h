#ifndef TABELLONE_H
#define TABELLONE_H

#include <iostream>
#include <vector>

class tabellone{
    public:
        tabellone();
        void stampa();
    private:
        std::vector<std::string> tabs;
};

#endif