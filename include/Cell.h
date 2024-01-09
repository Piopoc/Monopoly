// @author Pier Francesco Uliana, matricola: 2066593
#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>

#include "../include/Player.h"

//Si usa per le celle laterali e ne definisce il tipo: contiene i vari prezzi associati al tipo di terreno
struct Type
{
    const int purchase_land;    //Il prezzo per l'acquisto del terreno
    const int upgrade_to_house;    //Il prezzo per l'acquisto di una casa
    const int upgrade_to_hotel;    //Il prezzo per il miglioramento in hotel
    const int house_stay;    //Il prezzo per il pernottamento in una casa
    const int hotel_stay;    //Il prezzo per il pernottamento in un hotel
    const char identifier;    //Il carattere che identifica il tipo

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
        void add_occupant(Player* p);    //Aggiunge p al vettore dei giocatori che occupano la cella
        void remove_occupant(Player* p);    //Rimuove p dal vettore dei giocatori che occupano la cella
        Cell(const Cell&) = delete;
        Cell& operator=(const Cell&) = delete;
        virtual std::string to_string() const = 0;    //Restituisce una stringa di 13 caratteri che descrive la cella
        virtual ~Cell() = default;
    protected:
        std::vector<Player*> occupying{4};    //Vettore che contiene i giocatori che occupano la cella
        int number_of_occupants = 0;    //Il numero di giocatori che occupano la cella
        Cell() {};    
}; 

std::ostream& operator<<(std::ostream& o, const Cell& c);

//Sottoclasse che rappresenta una cella laterale
class SideCell : public Cell
{
    public:
        explicit SideCell(const Type& t);
        void add_owner(Player* p);    //aggiunge proprietario
        void remove_owner();    //Rimuove proprietario
        void upgrade_property();    //Se è presente un proprietario, migliora la proprietà
        Type get_type() const {return type;};    //Ritorna il tipo della cella 
        Player* get_owner() const;    //Ritorna il proprietario
        std::string to_string() const override;         
        bool has_owner() const {return owner;};    //Se ha un proprietario
        bool has_house() const {return (property == '*');};    //Se ha una casa
        bool has_hotel() const {return (property == '^');};    //Se ha un hotel
    private:
        Type type;    //Tipo di cella
        Player* owner = nullptr;    //Proprietario della cella
        char property = 0;    //Proprietà installata
};

//Sottoclasse che rappresenta una cella angolare
class EdgeCell : public Cell
{
    public:
        explicit EdgeCell(bool s);
        bool is_start() const {return is_start_cell;};    //Se è la cella di partenza
        std::string to_string() const override;
    private:
        bool is_start_cell;    //Indica se è la partenza o meno
};
#endif