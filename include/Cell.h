//@author Pier Francesco Uliana, matricola 2066593
#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
#include "../include/Player.h"
//Si usa per le celle laterali e ne definisce il tipo: contiene i vari prezzi associati al tipo di terreno

struct Type
{
    const int purchase_land;
    const int upgrade_to_house;
    const int upgrade_to_hotel;
    const int house_stay;
    const int hotel_stay;
    const char identifier;

    Type(int a, int b, int c, int d, int e, char i);
    Type(const Type& t);
};

//Inizializzano i 3 possibili tipi che possono avere le celle laterali
namespace types
{
    Type economic();
    Type standard();
    Type luxury();
};

class Cell
{        
    public:
        void add_occupant(Player* p);
        void remove_occupant(Player* p);

        Cell(const Cell&) = delete;
        Cell& operator=(const Cell&) = delete;

        virtual std::string to_string() const = 0;
        virtual ~Cell() = default;

    protected:
        std::vector<Player*> occupying{4}; 
        int number_of_occupants = 0;
        Cell() {};    
}; 

std::ostream& operator<<(std::ostream& o, const Cell& c);

//Sottoclasse che rappresenta una cella laterale
class SideCell : public Cell
{
    Type type;
    Player* owner = nullptr;
    char property = 0;

    public:
        explicit SideCell(const Type& t);

        void add_owner(Player* p);
        void remove_owner();

        void upgrade_property();

        Type get_type() const {return type;};
        Player* get_owner() const;
        char get_property() const {return property;};

        std::string to_string() const override;
        
        bool has_owner() const {return owner;};
        bool has_property() const {return !property;};
        bool has_house() const {return (property == '*');};
        bool has_hotel() const {return (property == '^');};
};

//Sottoclasse che rappresenta una cella angolare
class EdgeCell : public Cell
{
    bool is_start_cell;

    public:
        explicit EdgeCell(bool s);

        bool is_start() const {return is_start_cell;};

        std::string to_string() const override;
};
#endif