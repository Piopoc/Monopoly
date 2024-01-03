// @author Filippo Corradi, matricola: 2066680

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "../include/tabellone.h"
#include "../include/Cell.h"


tabellone::tabellone(){
    srand(time(NULL));

    int dim=28;
    int corner_box1=0;
    int corner_box2=7;
    int corner_box3=14;
    int corner_box4=21;

    //int p=rand()%4+1;
    int p=1;
    int e=8;
    int s=10;
    int l=6;

    int fraw=1;
    int fcolomn=65;

    std::shared_ptr<Cell> pointer;
    
    for(int i=0;i<dim;i++){
        if(p==1 && i==corner_box1){
            pointer.reset(new EdgeCell{true});
            tabs.push_back(pointer);
            start_position = i;
        }
        else if(p==2 && i==corner_box2){
            pointer.reset(new EdgeCell{true});
            tabs.push_back(pointer);
            start_position = i;
        }
        else if(p==3 && i==corner_box3){
            pointer.reset(new EdgeCell{true});
            tabs.push_back(pointer);
            start_position = i;
        }
        else if(p==4 && i==corner_box4){
            pointer.reset(new EdgeCell{true});
            tabs.push_back(pointer);
            start_position = i;
        }
        else if(i==corner_box1 || i==corner_box2 || i==corner_box3 || i==corner_box4 ){
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
                    // Trova la proprietà ancora disponibile
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

void tabellone::print_matrix(){
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

    // stampa della matrice
    for(int i=0;i<dim-1;i++){
        for(int j=0;j<dim;j++){
            std::cout<<matrix[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

int tabellone::parametrizzazione_bordo_x(int t) {
    if (!tabs.empty()) {
        t %= tabs.size();

        if (t <= 6) {
            return (1 + t);
        } else if (t <= 13) {
            return 8;
        } else if (t <= 20) {
            return (22 - t);
        } else {
            return 1;
        }
    } else {
        return -1;
    }
}


int tabellone::parametrizzazione_bordo_y(int t)
{
    if(!tabs.empty()){
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
        return -1;
    }
    
}

bool tabellone::beyond_start(Player* p, int from){
    return p->get_currpos()<from; //pettini
}

void tabellone::move(Player* p, int spostamenti){
    int from=p->get_currpos();
    tabs[from]->remove_occupant(p);
    int to=(from+spostamenti)%tabs.size();
    p->set_currpos(to);
    tabs[to]->add_occupant(p);
}

std::shared_ptr<Cell> tabellone::get_cell(int pos){
    if(pos>=0 && pos<tabs.size()){
        return tabs[pos];
    }
    else{
        throw std::out_of_range("indice supera il limite");
    }
}

std::string tabellone::get_cellname(int pos){
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

void tabellone::elimination(Player* p){
    for(int i=0; i < tabs.size(); i++){
        std::shared_ptr<SideCell> sideCell = std::dynamic_pointer_cast<SideCell>(tabs[i]);
        if(sideCell && p == sideCell->get_owner()){
            sideCell->remove_owner();
        }
    }
}

void tabellone::start_game(Player* p1, Player* p2, Player* p3, Player* p4){
    std::shared_ptr<Cell> start = get_cell(start_position);
    start->add_occupant(p1);
    start->add_occupant(p2);
    start->add_occupant(p3);
    start->add_occupant(p4);
}

void tabellone::show(Player* p1, Player* p2, Player* p3, Player* p4){
    print_matrix(); // magari questo non lo mettiamo dato che nel main stampa sempre
    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    players.push_back(p4);
    for(int j=0;j<players.size();j++){
        std::cout<<"Il giocatore "<<players[j]->get_ID()<<" ha "<<players[j]->get_money()<<" fiorini e possiede: \n";
        for(int i=0;i<tabs.size();i++){
            if(auto sideCell=std::dynamic_pointer_cast<SideCell>(tabs[i])){
                if(sideCell->get_owner()==players[j]){
                    if(sideCell->get_property()==0){
                        std::cout<<"- la proprietà "<<get_cell(i)<<" in "<<get_cellname(i)<<std::endl;
                    }
                    else if(sideCell->get_property()=='*'){
                        std::cout<<"- la casa "<<get_cell(i)<<" in "<<get_cellname(i)<<std::endl;
                    }
                    else{
                        std::cout<<"- l'albergo "<<get_cell(i)<<" in "<<get_cellname(i)<<std::endl;
                    }
                }
            }
        }
    }
}
void tabellone::bank_account(Player* p1, Player* p2, Player* p3, Player* p4){
    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    players.push_back(p4);

    for(int j=0;j<players.size();j++){
        std::cout<<"Il giocatore "<<players[j]->get_ID()<<" ha "<<players[j]->get_money()<<" fiorini \n";
    }
}
void tabellone::list_property(Player* p1, Player* p2, Player* p3, Player* p4){
    std::vector<Player*> players;
    players.push_back(p1);
    players.push_back(p2);
    players.push_back(p3);
    players.push_back(p4);
    // proprietà dove sono i giocatori
    for(int j=0;j<players.size();j++){
        for(int i=0;i<tabs.size();i++){
            if(auto sideCell=std::dynamic_pointer_cast<SideCell>(tabs[i])){
                if(sideCell->has_owner() && sideCell->get_owner()==players[j]){ // il problema sta qua !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    std::cout<<"Giocatore "<<players[j]->get_ID()<<" nella casella "<<get_cellname(i);
                    if(sideCell->get_property()==0){
                        std::cout<<" con una proprietà \n";
                    }
                    else if(sideCell->get_property()=='*'){
                        std::cout<<" con una casa \n";
                    }
                    else if(sideCell->get_property()=='^'){
                        std::cout<<" con un albergo \n";
                    }
                    else{
                        std::cout<<"\n";
                    }
                }
            }
        }
    }
    // proprietà dove non sono i giocatori
    for(int i=0;i<tabs.size();i++){
        if(auto sideCell=std::dynamic_pointer_cast<SideCell>(tabs[i])){
            if(!sideCell->has_owner() && (sideCell->has_house() || sideCell->has_hotel )){ // qua manca la condizione che dice se c'è una proprietà
                if(sideCell->get_property()==0){
                    std::cout<<"Casella "<<get_cellname(i)<<" con proprietà \n";
                }
                else if(sideCell->get_property()=='*'){
                    std::cout<<"Casella "<<get_cellname(i)<<" con casa \n";
                }
                else if(sideCell->get_property()=='^'){
                    std::cout<<"Casella "<<get_cellname(i)<<" con albergo \n";
                }
            }
        }
    }
}