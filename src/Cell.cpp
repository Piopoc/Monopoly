//Pier Francesco Uliana, matricola 2066593
#include <iostream>
#include "../include/Cell.h"

//Type
Type::Type(int a, int b, int c, int d, int e, char i)
    : purchase_terrain{a}, upgrade_to_house{b}, upgrade_to_hotel{c}, house_stay{d}, hotel_stay{e}, identifier{i}
{}

Type::Type(const Type& t)
    : purchase_terrain{t.purchase_terrain}, upgrade_to_house{t.upgrade_to_house}, upgrade_to_hotel{t.upgrade_to_hotel}, house_stay{t.house_stay}, hotel_stay{t.hotel_stay}, identifier{t.identifier}
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
void Cell::add_occupant(char p)
{
    for(int i = 0; i < number_of_occupants; i++)
    {
        if(occupying[i] == p)
        {
            return;
        }
    }

    occupying[number_of_occupants++] = p;
}

//Rimuove dalla lista dei giocatori che occupano la casella, FALLISCE SILENZIOSAMENTE SE NON PRESENTE
void Cell::remove_occupant(char p)
{
    for(int i = 0; i < number_of_occupants; i++)
    {
        if(occupying[i] == p)
        {
            for(int j = i; j < number_of_occupants - 1; j++)
            {
                occupying[j] = occupying[j + 1];
            }

            number_of_occupants--;
            break;
        }
    }
}

std::ostream& operator<<(std::ostream& o, const Cell& c)
{
    return o << c.to_string();
}

//SideCell
SideCell::SideCell(const Type& t, const std::string& c)
    : type{t}, property{0}
{coordinates = c;}

//FALLISCE SILENZIONSAMENTE SE E' GIA' PRESENTE UN PROPRIETARIO
void SideCell::add_owner(char p)
{
    if(!owner)
    {
        owner = p;
    }
}  

//FALLISCE SILENZIOSAMENTE SE NON E' PRESENTE UN PROPRIETARIO
void SideCell::remove_owner()
{
    if(owner)
    {
        owner = 0;
        property = 0;
    }
}

//FALLISCE SILENZIOSAMENTE SE NON HA PROPRIETARIO O SE E' GIA' PRESENTE UN HOTEL
void SideCell::upgrade_property()
{
    if(owner)
    {
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
}

std::string SideCell::to_string() const
{
    std::string s = "| ";
    s += type.identifier;
    s += property;
    
    if(number_of_occupants)
    {
        for(int i = 0; i < number_of_occupants; i++)
        {
            s += occupying[i];
            s += " ";
        }
    }

    else
    {
        s += " ";
    }

    s += "|";
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
            s += occupying[i];
            s += " ";
        }
    }

    else
    {
        s += " ";
    }

    s += "|";
    return s;
}