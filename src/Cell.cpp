// @author Pier Francesco Uliana, matricola 2066593
#include <iostream>
#include <vector>
#include <exception>
#include "../include/Cell.h"

/*Type*/
Type::Type(int a, int b, int c, int d, int e, char i)
    : purchase_land{a}, upgrade_to_house{b}, upgrade_to_hotel{c}, house_stay{d}, hotel_stay{e}, identifier{i}
{}

Type::Type(const Type& t)
    : purchase_land{t.purchase_land}, upgrade_to_house{t.upgrade_to_house}, upgrade_to_hotel{t.upgrade_to_hotel}, house_stay{t.house_stay}, hotel_stay{t.hotel_stay}, identifier{t.identifier}
{}



/*Types*/
//Definisce il tipo "economica"
Type types::economic()
{
    return Type{6, 3, 3, 2, 4, 'E'};
}

//Definisce il tipo "standard"
Type types::standard()
{
    return Type{10, 5, 5, 4, 8, 'S'};
}

//Definisce il tipo "lusso"
Type types::luxury()
{
    return Type{20, 10, 10, 7, 14, 'L'};
}



/*Cell*/
//Aggiunge p al vettore dei giocatori che occupano la casella, lancia eccezione se già presente o se nullptr
void Cell::add_occupant(Player* p)
{
    if(!p)
    {
        throw std::logic_error{"Il puntatore è nullptr"};
    }
    
    for(int i = 0; i < number_of_occupants; i++)
    {
        if(occupying[i]->get_ID() == p->get_ID())
        {
            throw std::logic_error{"Giocatore già presente"};
        }
    }

    occupying[number_of_occupants++] = p;
}

//Rimuove p dal vettore dei giocatori che occupano la casella, lancia eccezione se non presente o se è nullptr
void Cell::remove_occupant(Player* p)
{
    if(!p)
    {
        throw std::logic_error{"Il puntatore è nullptr"};
    }
    
    for(int i = 0; i < number_of_occupants; i++)
    {
        if(occupying[i]->get_ID() == p->get_ID())
        {
            for(int j = i; j < number_of_occupants - 1; j++)
            {
                occupying[j] = occupying[j + 1];
            }

            number_of_occupants--;
            return;
        }
    }

    throw std::logic_error{"Giocatore non presente nella casella"};
}

std::ostream& operator<<(std::ostream& o, const Cell& c)
{
    return o << c.to_string();
}



/*SideCell*/
SideCell::SideCell(const Type& t)
    : type{t}
{}

//Aggiunge il proprietario, lancia eccezione se già presente o se nullptr
void SideCell::add_owner(Player* p)
{
    if(!p)
    {
        throw std::logic_error{"Il puntatore è nullptr"};
    }
    
    if(owner)
    {  
        throw std::logic_error{"La casella ha già un proprietario"};
    }

    owner = p;
}  

//Rimuove il proprietario, lancia eccezione se non presente
void SideCell::remove_owner()
{
    if(!owner)
    {
        throw std::logic_error{"La casella non ha un proprietario"};
    }
    
    owner = nullptr;
    property = 0;
}

//Migliora la proprietà, lancia eccezione se non è presente un proprietario o se è già presente un hotel
void SideCell::upgrade_property()
{
    if(!owner)
    {
        throw std::logic_error{"La casella non ha un proprietario"};    
    }

    switch(property)
    {
        case 0:
            property = '*';
        break;
        case '*':
            property = '^';
        break;
        case '^':
            throw std::logic_error{"La proprietà non può essere migliorata perché è già presente un hotel"};
        break;
    }
}

//Restituisce il proprietario, lancia eccezione se non presente
Player* SideCell::get_owner() const
{
    if(!owner)
    {
        throw std::logic_error{"La casella non ha un proprietario"};
    }

    return owner;
}

//Restituisce una stringa di 13 caratteri che descrive la casella: di questa ne stampa il tipo,
//l'eventuale casa/hotel installata e la lista dei giocatori che la occupano
std::string SideCell::to_string() const
{
    std::string s = "| ";
    //tipo
    s += type.identifier;
    //proprietà
    if(property)
    {
        s += property;
    }

    //lista dei giocatori che occupano la casella
    if(number_of_occupants)
    {   
        for(int i = 0; i < number_of_occupants; i++)
        {
            s += (occupying[i]->get_ID() + 48);  //Conversione da int a char
            s += " ";
        }
    }

    else
    {
        s += " ";
    }

    s += "|";

    //aggiunge spazi all'inizio e alla fine per far sì che la stringa sia di 13 caratteri
    int diff = 13 - s.size();

    if(diff)
    {
        for(int a = 0; a < diff / 2; a++)
        {
            s = " " + s;
        }

        for(int b = 0; b < diff - (diff / 2); b++)
        {
            s += " ";
        }
    }
    
    return s;
}



/*EdgeCell*/
EdgeCell::EdgeCell(bool s)
    : is_start_cell{s}
{}

//Restituisce una stringa di 13 caratteri che descrive la casella: stampa P se è la cella di partenza e stampa
//la lista dei giocatori che la occupano
std::string EdgeCell::to_string() const
{
    std::string s = "| ";
    switch(is_start_cell)
    {
        case 0:
            s += ((number_of_occupants) ? "" : " ");
        break;
        
        //se è partenza
        case 1:
            s += "P";
        break;
    }
    
    //lista dei giocatori che occupano la casella
    if(number_of_occupants)
    {
        for(int i = 0; i < number_of_occupants; i++)
        {
            s += (occupying[i]->get_ID() + 48);
            s += " ";
        }
    }

    else
    {
        s += " ";
    }

    s += "|";

    //aggiunge spazi all'inizio e alla fine per far sì che la stringa sia di 13 caratteri
    int diff = 13 - s.size();

    if(diff)
    {
        for(int a = 0; a < diff / 2; a++)
        {
            s = " " + s;
        }

        for(int b = 0; b < diff - (diff / 2); b++)
        {
            s += " ";
        }
    }

    return s;
}