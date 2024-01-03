// @author Pier Francesco Uliana, matricola 2066593
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

//Classe che rappresenta una cella generica
class Cell
{        
    public:
        //Aggiunge p al vettore dei giocatori che occupano la cella
        void add_occupant(Player* p);
        //Rimuove p dal vettore dei giocatori che occupano la cella
        void remove_occupant(Player* p);

        Cell(const Cell&) = delete;
        Cell& operator=(const Cell&) = delete;

        //Restituisce una stringa di 13 caratteri che descrive la cella
        virtual std::string to_string() const = 0;
        virtual ~Cell() = default;

    protected:
        //Vettore che contiene i giocatori che occupano la cella
        std::vector<Player*> occupying{4}; 
        //Il numero di giocatori che occupano la cella
        int number_of_occupants = 0;
        Cell() {};    
}; 

std::ostream& operator<<(std::ostream& o, const Cell& c);

//Sottoclasse che rappresenta una cella laterale
class SideCell : public Cell
{
    //Tipo di cella
    Type type;
    //Proprietario della cella
    Player* owner = nullptr;
    //Proprietà
    char property = 0;

    public:
        explicit SideCell(const Type& t);

        //aggiunge proprietario
        void add_owner(Player* p);
        //Rimuove proprietario
        void remove_owner();

        //Se è presente un proprietario, migliora la proprietà
        void upgrade_property();

        //Ritorna il tipo della cella
        Type get_type() const {return type;};
        //Ritorna il proprietario 
        Player* get_owner() const;
        //Ritorna la proprietà
        char get_property() const;

        std::string to_string() const override;
        
        //Se ha un proprietario 
        bool has_owner() const {return owner;};
        //Se ha una casa
        bool has_house() const {return (property == '*');};
        //Se ha un hotel
        bool has_hotel() const {return (property == '^');};
};

//Sottoclasse che rappresenta una cella angolare
class EdgeCell : public Cell
{
    //Indica se è la partenza o meno
    bool is_start_cell;

    public:
        explicit EdgeCell(bool s);

        //Se è la cella di partenza
        bool is_start() const {return is_start_cell;};

        std::string to_string() const override;
};
#endif