// @author Filippo Corradi, matricola: 2066680

#include <iostream>
#include <cstdlib>
#include <ctime>
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

    
    EdgeCell empty(false,"");
    EdgeCell start(true,"");
    SideCell eco(types::economic(),"");
    SideCell stand(types::standard(),"");
    SideCell lux(types::luxury(),"");

    for(int i=0;i<dim;i++){
        if(i==corner_box1 || i==corner_box2 || i==corner_box3 || i==corner_box4){
            tabs.push_back(&empty);
        }
        if(i>corner_box1 && i!=corner_box2 && i!=corner_box3 && i!=corner_box4){
            if (e > 0 || s > 0 || l > 0) {
                int temp = rand() % 3 + 1;
                if (e > 0 && temp == 1) {
                        tabs.push_back(&eco);
                        e--;
                    } else if (s > 0 && temp == 2) {
                        tabs.push_back(&stand);
                        s--;
                    } else if (l > 0 && temp == 3) {
                        tabs.push_back(&lux);
                        l--;
                    } else {
                        // Trova la proprietà ancora disponibile
                        if (e > 0) {
                            tabs.push_back(&eco);
                            e--;
                        } else if (s > 0) {
                            tabs.push_back(&stand);
                            s--;
                        } else if (l > 0) {
                            tabs.push_back(&lux);
                            l--;
                        }
                    }
            }
        }
        if(p==1 && i==corner_box1){
            tabs.push_back(&start);
        }
        else if(p==2 && i==corner_box2){
            tabs.push_back(&start);
        }
        else if(p==3 && i==corner_box3){
            tabs.push_back(&start);
        }
        else{
            tabs.push_back(&start);
        }
    }
}

void tabellone::stampa(){
    static const int dim=10;
    std::string matrix[dim][dim];
    int fraw=1;
    int fcolomn=65;

    int a=0; 
    int b=7;
    int c=20;
    int d=27;    

    /*
    // carica della matrice traimte vector
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(i==0 && j==0){
                matrix[i][j]="   ";
            }
            else if(j==0 && i<dim-1){
                if(i==dim-1){
                    matrix[i][j]="\n";
                }
                else{
                    matrix[i][j]=std::string(1, static_cast<char>(fcolomn++));
                }
            }
            else if(i==0 && j<dim-1){
                matrix[i][j]="    "+std::to_string(fraw++)+"    ";
            }
            else if(j==dim-2){
                if(b<14){
                    if(b==7){
                        matrix[i][j]=tabs[b++]->to_string();
                    }
                    else{
                        matrix[i][j]="                                                      "+tabs[b++]->to_string();
                    }
                }
            }
            else if(i==1){
                if(a<7){
                    if(a==0){
                        matrix[i][j]="  "+tabs[a++]->to_string();
                    }
                    else{
                        matrix[i][j]=tabs[a++]->to_string();
                    }
                }
            }
            else if(j==1){
                if(d>=21){
                    matrix[i][j]="  "+tabs[d--]->to_string();
                }
            }
            else if(i==dim-2){
                 if(c>=14){
                    matrix[i][j]=tabs[c--]->to_string();
                }
            }
            
        }
    }*/

    matrix[0][0] = " ";
    matrix[1][0] = " ";
    matrix[0][1] = " ";

    for(int i = 1; i < dim- 1; i++)
    {
        matrix[i][0]=std::string(1, static_cast<char>(fcolomn++));
        matrix[0][i]=std::to_string(fraw++);
    }

    for(int t = 0; t <= 27; t++)
    {
        matrix[parametrizzazione_bordo_y(t)][parametrizzazione_bordo_x(t)] = tabs[0] -> to_string();
    }

    for(int y = 2; y <= 7; y++)
    {
        for(int x = 2; x <= 7; x++)
        {
            matrix[y][x] = "0";
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

int tabellone::parametrizzazione_bordo_x(int t)
{
    //NON E' GESTITO IL CASO DI t NEGATIVO
    t %= tabs.size();

    if(t <= 6)
    {
        return (1 + t);
    }

    else if(t <= 13)
    {
        return 8;
    }

    else if(t <= 20)
    {
        return (22 - t);
    }

    else
    {
        return 1;
    }
}

int tabellone::parametrizzazione_bordo_y(int t)
{
    //NON E' GESTITO IL CASO DI t NEGATIVO
    t %= tabs.size();

    if(t <= 6)
    {
        return 1;
    }

    else if(t <= 13)
    {
        return (t - 6);
    }

    else if(t <= 20)
    {
        return 8;
    }

    else
    {
        return (29 - t);
    }
}

std::string tabellone::create_coordinates(int t)
{
    char x = t + 49;
    char y = t + 65;
    std::string s = y + x;
    return s;
}