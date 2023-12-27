#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>

class bankAccount{
    public:
        void saldo();
        void versa(int x);
        void preleva(int x);
    private:
        int deposito;
};

#endif