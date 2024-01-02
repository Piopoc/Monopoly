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

    int p=rand()%4+1;
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

/* void tabellone::delete_matrix(std::string**matrix,int dim){
    for(int i=0;i<dim;i++){
        delete[]matrix[i];
    }
    delete[]matrix;
} */

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
    /*//backend
    std::shared_ptr<Cell> start = get_cell(0);
    start->add_occupant(p1);
    start->add_occupant(p2);
    start->add_occupant(p3);
    start->add_occupant(p4);
    //frontend
    const int dim=10;
    std::string** matrix=charge_matrix();
    int begin=0;
    for(int i=0;i<tabs.size();i++){
        if((tabs[i]->to_string()).find("P")!=std::string::npos){
            begin=i;
        }
    }

    std::string value=tabs[begin]->to_string();

    for(int i=0;i<dim-1;i++){
        for(int j=0;j<dim;j++){
            if(value==matrix[i][j]){
                std::string temp=value;
                for(int k=0;k<value.length();k++){
                    if(value[k]=='P'){
                        temp[k]='P'+31+32+33+34;
                    }
                }
                matrix[i][j]=temp;
            }
        }
    }*/
}