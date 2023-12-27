#include <iostream>
#include "../include/bankAccount.h"

bankAccount::bankAccount()
{
    deposito = 0;
}
bool bankAccount::isEmpty()
{
    return deposito == 0;
}
int bankAccount::saldo()
{
    return deposito;
}
void bankAccount::versa(int x)
{
    deposito += x;
}
void bankAccount::preleva(int x)
{
    if(deposito-x<0) throw std::exception();
    deposito -= x;
}