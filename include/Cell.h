//Pier Francesco Uliana, matricola 2066593
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
        void add_occupant(Player p); //vanno messi in reference i player altrimenti si rischia inconsisenza
        void remove_occupant(Player p); //vanno messi in reference i player altrimenti si rischia inconsisenza

        Cell(const Cell&) = delete;
        Cell& operator=(const Cell&) = delete;

        std::string get_coordinates() const {return coordinates;};

        virtual std::string to_string() const = 0;
        virtual ~Cell() = default;

    protected:
        std::vector<Player> occupying{4};
        int number_of_occupants = 0;
        std::string coordinates;
        Cell() {};    
}; 

std::ostream& operator<<(std::ostream& o, const Cell& c);

//Sottoclasse che rappresenta una cella laterale
class SideCell : public Cell
{
    Type type;
    Player* owner;
    char property = 0;
    bool is_owned = 0;

    public:
        SideCell(const Type& t, const std::string& c);

        void add_owner(Player* p);
        void remove_owner();

        void upgrade_property();

        Type get_type() const {return type;};
        Player* get_owner() const;
        char get_property() const {return property;};

        std::string to_string() const override;
        
        bool has_owner() const {return is_owned;};
        bool has_house() const {return (property == '*');};
        bool has_hotel() const {return (property == '^');};
};

//Sottoclasse che rappresenta una cella angolare
class EdgeCell : public Cell
{
    bool is_start_cell;

    public:
        EdgeCell(bool s, const std::string& c);

        bool is_start() const {return is_start_cell;};

        std::string to_string() const override;
};
#endif