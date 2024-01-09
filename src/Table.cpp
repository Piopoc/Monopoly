// @author Filippo Corradi, matricola: 2066680

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "../include/Table.h"
#include "../include/Cell.h"

// costruttore
Table::Table(){
    srand(time(NULL));

    int dim=28;
    int corner_box1=0;
    int corner_box2=7;
    int corner_box3=14;
    int corner_box4=21;

    int e=8;
    int s=10;
    int l=6;

    int fraw=1;
    int fcolomn=65;

    std::shared_ptr<Cell> pointer;
    
    for(int i=0;i<dim;i++){
        if(i==corner_box1){
            pointer.reset(new EdgeCell{true});
            tabs.push_back(pointer);
        }
        else if(i==corner_box2 || i==corner_box3 || i==corner_box4 ){
            pointer.reset(new EdgeCell{false});
            tabs.push_back(pointer);
        }
        else if(i>corner_box1 && i!=corner_box2 && i!=corner_box3 && i!=corner_box4){
            if (e > 0 || s > 0 || l > 0) {
                int temp = rand() % 3 + 1;
                if (e > 0 && temp == 1) {
                    pointer.reset(new SideCell{types::economic()});
                    tabs.push_back(pointer);
                    e--;
                } else if (s > 0 && temp == 2) {
                    pointer.reset(new SideCell{types::standard()});
                    tabs.push_back(pointer);
                    s--;
                } else if (l > 0 && temp == 3) {
                    pointer.reset(new SideCell{types::luxury()});
                    tabs.push_back(pointer);
                    l--;
                } else {
                    if (e > 0) {
                        pointer.reset(new SideCell{types::economic()});
                        tabs.push_back(pointer);
                        e--;
                    } else if (s > 0) {
                        pointer.reset(new SideCell{types::standard()});
                        tabs.push_back(pointer);
                        s--;
                    } else if (l > 0) {
                        pointer.reset(new SideCell{types::luxury()});
                        tabs.push_back(pointer);
                        l--;
                    }
                }
            }
        }
    }
}

// stampa il tabellone tramite il caricamento degli elementi in una "matrice"
void Table::print_matrix() const{
    static const int dim=10;
    std::string matrix[dim][dim];
    int fraw=1;
    int fcolomn=65;  

    matrix[0][0] = " ";

    for(int i = 1; i < dim- 1; i++)
    {
        matrix[i][0]=std::string(1, static_cast<char>(fcolomn++));
        matrix[0][i]="      "+std::to_string(fraw++)+"      ";
    }

    for(int t = 0; t <tabs.size(); t++)
    {
        matrix[parametrizzazione_bordo_y(t)][parametrizzazione_bordo_x(t)] = tabs[t] -> to_string();
    }

    for(int y = 2; y < dim-2; y++)
    {
        for(int x = 2; x < dim-2; x++)
        {
            matrix[y][x] = "             ";
        }
    }

    for(int i=0;i<dim-1;i++){
        for(int j=0;j<dim;j++){
            std::cout<<matrix[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

// la componente x della curva che parametrizza il bordo
int Table::parametrizzazione_bordo_x(int t) const{
    if (tabs.size() == 28) {
        while(t < 0) {
            t += tabs.size();
        }
        t %= tabs.size();
        
        if (t <= 6) {
            return (1 + t);
        }
        else if (t <= 13) {
            return 8;
        }
        else if (t <= 20) {
            return (22 - t);
        }
        else {
            return 1;
        }
    } else {
        throw std::runtime_error("Non sono presenti tutte le caselle");
    }
}

// la componente y della curva che parametrizza il bordo
int Table::parametrizzazione_bordo_y(int t) const{
    if(tabs.size() == 28){
        while(t < 0) {
            t += tabs.size();
        }
        t %= tabs.size();

        if(t <= 6){
            return 1;
        }
        else if(t <= 13){
            return (t - 6);
        }
        else if(t <= 20){
            return 8;
        }
        else{
            return (29 - t);
        }
    }
    else{
        throw std::runtime_error("Non sono presenti tutte le caselle");
    }
    
}

// verifica se player passa per casella con P
bool Table::beyond_start(Player* p, int from) const{
    return p->get_currpos()<from;
}

// spostamento del player da posizione attuale a posizione indicata da lancio dei dadi
void Table::move(Player* p, int spostamenti){
    int from=p->get_currpos();
    tabs[from]->remove_occupant(p);
    int to=(from+spostamenti)%tabs.size();
    p->set_currpos(to);
    tabs[to]->add_occupant(p);
}

// restituisce la ref alla cell dell'indice array
std::shared_ptr<Cell> Table::get_cell(int pos){
    if(pos>=0 && pos<tabs.size()){
        return tabs[pos];
    }
    else{
        throw std::out_of_range("indice supera il limite");
    }
}

// ritorna casella stile scacchiera o campo di battaglia navale
std::string Table::get_cellname(int pos) const{
    if(pos < 0 || pos >= tabs.size())
    {
        throw std::logic_error("Casella non trovata");
    }

    char x = parametrizzazione_bordo_x(pos) + 48;
    char y = parametrizzazione_bordo_y(pos) + 64;
    std::string s = "";
    s += y;
    s += x;
    return s;
}

// elimina tutte le proprietà
void Table::elimination(Player* p){
    for(int i=0; i < tabs.size(); i++){
        std::shared_ptr<SideCell> sideCell = std::dynamic_pointer_cast<SideCell>(tabs[i]);
        if(sideCell && sideCell->has_owner()){
            if(p == sideCell->get_owner()){
                sideCell->remove_owner();
            }
        }
    }
}

// giocatori sulla casella di partenza
void Table::start_game(Player* p1, Player* p2, Player* p3, Player* p4){
    std::shared_ptr<Cell> start = get_cell(0);
    start->add_occupant(p1);
    start->add_occupant(p2);
    start->add_occupant(p3);
    start->add_occupant(p4);
}

// mostra quanti fiorini possiedono i giocatori che non sono stati eliminati
void Table::bank_account(std::queue<Player*>& pList, Player* pt){
    std::cout << "Il giocatore " << pt->get_ID() << " ha " << pt->get_money() << " fiorini \n";
    int size = pList.size();
    for(int j=0;j<size;j++){
        Player* temp=pList.front();
        std::cout << "Il giocatore " << temp->get_ID() << " ha " << temp->get_money() << " fiorini \n";
        pList.pop();
        pList.push(temp);
    }
}

// mostra le proprietà di ogni giocatore ancora in gioco
void Table::list_property(std::queue<Player*>& pList, Player* pt){
    std::cout << "Giocatore " << pt->get_ID() << ": ";
    for(int i = 0; i < tabs.size(); i++){
        if(std::shared_ptr<SideCell> sideCell = std::dynamic_pointer_cast<SideCell>(tabs[i])){
            if(sideCell->has_owner() && sideCell->get_owner()==pt){
                std::cout << get_cellname(i) << " ";
            }
        }
    }
    std::cout << std::endl;
    int size = pList.size();
    for(int j=0;j<size;j++){
        Player* temp=pList.front();
        std::cout << "Giocatore " << temp->get_ID() << ": ";
        for(int i = 0; i < tabs.size(); i++){
            if(std::shared_ptr<SideCell> sideCell = std::dynamic_pointer_cast<SideCell>(tabs[i])){
                if(sideCell->has_owner() && sideCell->get_owner()==temp){
                    std::cout << get_cellname(i) << " ";
                }
            }
        }
        std::cout << std::endl;
        pList.pop();
        pList.push(temp);
    }
}