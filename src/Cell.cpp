//Pier Francesco Uliana, matricola 2066593
#include <iostream>
#include <vector>
#include <exception>
#include "../include/Cell.h"

//Type
Type::Type(int a, int b, int c, int d, int e, char i)
    : purchase_land{a}, upgrade_to_house{b}, upgrade_to_hotel{c}, house_stay{d}, hotel_stay{e}, identifier{i}
{}

Type::Type(const Type& t)
    : purchase_land{t.purchase_land}, upgrade_to_house{t.upgrade_to_house}, upgrade_to_hotel{t.upgrade_to_hotel}, house_stay{t.house_stay}, hotel_stay{t.hotel_stay}, identifier{t.identifier}
{}

//Types
Type types::economic()
{
    return Type{6, 3, 3, 2, 4, 'E'};
}

Type types::standard()
{
    return Type{10, 5, 5, 4, 8, 'S'};
}

Type types::luxury()
{
    return Type{20, 10, 10, 7, 14, 'L'};
}

//Cell
//Aggiunge alla lista dei giocatori che occupano la casella, FALLISCE SILENZIOSAMENTE SE GIA' PRESENTE
void Cell::add_occupant(Player p)
{
    for(int i = 0; i < number_of_occupants; i++)
    {
        if(occupying[i].getID() == p.getID())
        {
            throw std::logic_error{"Giocatore già presente"};
        }
    }

    occupying[number_of_occupants++] = p;
}

//Rimuove dalla lista dei giocatori che occupano la casella, FALLISCE SILENZIOSAMENTE SE NON PRESENTE
void Cell::remove_occupant(Player p)
{
    for(int i = 0; i < number_of_occupants; i++)
    {
        if(occupying[i].getID() == p.getID())
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

//SideCell
SideCell::SideCell(const Type& t, const std::string& c)
    : type{t}
{coordinates = c;}

//FALLISCE SILENZIONSAMENTE SE E' GIA' PRESENTE UN PROPRIETARIO
void SideCell::add_owner(Player* p)
{
    if(is_owned)
    {  
        throw std::logic_error{"La casella ha già un proprietario"};
    }

    is_owned = true;
    owner = p;
}  

//FALLISCE SILENZIOSAMENTE SE NON E' PRESENTE UN PROPRIETARIO
void SideCell::remove_owner()
{
    if(!is_owned)
    {
        throw std::logic_error{"La casella non ha un proprietario"};
    }

    is_owned = false;
    property = 0;
}

//FALLISCE SILENZIOSAMENTE SE NON HA PROPRIETARIO O SE E' GIA' PRESENTE UN HOTEL
void SideCell::upgrade_property()
{
    if(!is_owned)
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
    }
}

Player* SideCell::get_owner() const
{
    if(!is_owned)
    {
        throw std::logic_error{"La casella non ha un proprietario"};
    }

    return owner;
}

std::string SideCell::to_string() const
{
    std::string s = "| ";
    s += type.identifier;
    if(property)
    {
        s += property;
    }

    if(number_of_occupants)
    {   
        for(int i = 0; i < number_of_occupants; i++)
        {
            s += (occupying[i].getID() + 48);  //Conversione da int a char
            s += " ";
        }
    }

    else
    {
        s += " ";
    }

    s += "|";

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

//EdgeCell
EdgeCell::EdgeCell(bool s, const std::string& c)
    : is_start_cell{s}
{coordinates = c;}

std::string EdgeCell::to_string() const
{
    std::string s = "| ";
    switch(is_start_cell)
    {
        case 0:
            s += ((number_of_occupants) ? "" : " ");
        break;
        
        case 1:
            s += "P";
        break;
    }
    
    if(number_of_occupants)
    {
        for(int i = 0; i < number_of_occupants; i++)
        {
            s += (occupying[i].getID() + 48);
            s += " ";
        }
    }

    else
    {
        s += " ";
    }

    s += "|";

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