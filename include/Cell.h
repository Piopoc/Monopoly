//Pier Francesco Uliana, matricola 2066593
#ifndef CELL_H
#define CELL_H
#include <iostream>
//Si usa per le celle laterali e ne definisce il tipo: contiene i vari prezzi associati al tipo di terreno
struct Type
{
    const int purchase_terrain;
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

//I GIOCATORI SONO AL MOMENTO RAPPRESETATI MEDIANTE char, NON APPENA SARA' DISPONIBILE LA CLASSE Player SI EFFETTUERA' LA SOSTITUZIONE
class Cell
{        
    public:
        void add_occupant(char p);
        void remove_occupant(char p);

        Cell(const Cell&) = delete;
        Cell& operator=(const Cell&) = delete;

        std::string get_coordinates() {return coordinates;};

        virtual std::string to_string() const = 0;

    protected:
        char occupying[4];
        int number_of_occupants = 0;
        std::string coordinates;
        Cell() {};    
}; 

std::ostream& operator<<(std::ostream& o, const Cell& c);

//Sottoclasse che rappresenta una cella laterale
class SideCell : public Cell
{
    Type type;
    char owner;
    char property;

    public:
        SideCell(const Type& t, const std::string& c);

        void add_owner(char p);
        void remove_owner();

        void upgrade_property();

        Type get_type() {return type;};
        char get_owner() {return owner;};
        char get_property() {return property;};

        std::string to_string() const;
};

//Sottoclasse che rappresenta una cella angolare
class EdgeCell : public Cell
{
    bool is_start_cell;

    public:
        EdgeCell(bool s, const std::string& c);

        bool is_start() {return is_start_cell;};

        std::string to_string() const;
};
#endif