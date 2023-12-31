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
            pointer.reset(new EdgeCell{true, ""});
            tabs.push_back(pointer);
        }
        else if(p==2 && i==corner_box2){
            pointer.reset(new EdgeCell{true, ""});
            tabs.push_back(pointer);
        }
        else if(p==3 && i==corner_box3){
            pointer.reset(new EdgeCell{true, ""});
            tabs.push_back(pointer);
        }
        else if(p==4 && i==corner_box4){
            pointer.reset(new EdgeCell{true, ""});
            tabs.push_back(pointer);
        }
        else if(i==corner_box1 || i==corner_box2 || i==corner_box3 || i==corner_box4 ){
            pointer.reset(new EdgeCell{false, ""});
            tabs.push_back(pointer);
        }
        else if(i>corner_box1 && i!=corner_box2 && i!=corner_box3 && i!=corner_box4){
            if (e > 0 || s > 0 || l > 0) {
                int temp = rand() % 3 + 1;
                if (e > 0 && temp == 1) {
                        pointer.reset(new SideCell{types::economic(), ""});
                        tabs.push_back(pointer);
                        e--;
                    } else if (s > 0 && temp == 2) {
                        pointer.reset(new SideCell{types::standard(), ""});
                        tabs.push_back(pointer);
                        s--;
                    } else if (l > 0 && temp == 3) {
                        pointer.reset(new SideCell{types::luxury(), ""});
                        tabs.push_back(pointer);
                        l--;
                    } else {
                        // Trova la proprietà ancora disponibile
                        if (e > 0) {
                            pointer.reset(new SideCell{types::economic(), ""});
                            tabs.push_back(pointer);
                            e--;
                        } else if (s > 0) {
                            pointer.reset(new SideCell{types::standard(), ""});
                            tabs.push_back(pointer);
                            s--;
                        } else if (l > 0) {
                            pointer.reset(new SideCell{types::luxury(), ""});
                            tabs.push_back(pointer);
                            l--;
                        }
                    }
            }
        }
    }
}

void tabellone::stampa(){
    static const int dim=10;
    std::string matrix[dim][dim];
    int fraw=1;
    int fcolomn=65;  

    matrix[0][0] = " ";
    matrix[1][0] = " ";
    matrix[0][1] = " ";

    for(int i = 1; i < dim- 1; i++)
    {
        matrix[i][0]=std::string(1, static_cast<char>(fcolomn++));
        matrix[0][i]="      "+std::to_string(fraw++)+"      ";
    }

    for(int t = 0; t <tabs.size(); t++)
    {
        matrix[parametrizzazione_bordo_y(t)][parametrizzazione_bordo_x(t)] = tabs[t] -> to_string();
    }

    for(int y = 2; y <= 7; y++)
    {
        for(int x = 2; x <= 7; x++)
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

std::string tabellone::create_coordinates(int t)
{
    char x = parametrizzazione_bordo_x(t) + 49;
    char y = parametrizzazione_bordo_y(t) + 65;
    std::string s = std::to_string(y + x);
    return s;
}

/* Cell tabellone::whereIs(Player p)
{
    for(int i=0;i<"vectorPlayer".size();i++){
        if(p.getID()=="vectorPlayer[i]".getID()){
            return tabs[i];
        }
    }
    throw std::exception("Il giocatore non è presente nella board");
} 

bool tabellone::beyondStart(Player p){
    Cell from=whereIs(p);
    move(p,from,numerosalti);
    Cell to=whereIs(p);
    return to<from;
}*/