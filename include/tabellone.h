#ifndef TABELLONE_H
#define TABELLONE_H

#include <iostream>

class tabellone{
    public:
        tabellone();
        const int getR();
        const int getC();
        void stampa();
    private:
        static const int righe=9;
        static const int colon=9;
        std::string tabs[righe][colon];
};

#endif