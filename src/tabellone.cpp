// @author Filippo Corradi, matricola: 2066680

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/tabellone.h"


tabellone::tabellone(){
    srand(time(NULL));

    int dim=64;
    int corner_box1=36;
    int corner_box2=43;
    int corner_box3=50;
    int corner_box4=57;

    int p=rand()%4+1;
    int e=8;
    int s=10;
    int l=6;

    int fraw=1;
    int fcolomn=65;

    for(int i=0;i<dim;i++){
        if(i==0){
            tabs.push_back("");
        }
        if(i>0 && i<9){
            tabs.push_back("    "+std::to_string(fraw++)+"    ");
        }
        if(i>8 && i<28){
            tabs.push_back("   ");
        }
        if(i>27 && i<36){
            tabs.push_back(std::string(1, static_cast<char>(fcolomn++)));
        } 
        if(i==corner_box1 || i==corner_box2 || i==corner_box3 || i==corner_box4){
            tabs.push_back("  |   |  ");
        }
        if(i>corner_box1 && i!=corner_box2 && i!=corner_box3 && i!=corner_box4){
            if (e > 0 || s > 0 || l > 0) {
                int temp = rand() % 3 + 1;
                if (e > 0 && temp == 1) {
                        tabs.push_back("  | E |  ");
                        e--;
                    } else if (s > 0 && temp == 2) {
                        tabs.push_back("  | S |  ");
                        s--;
                    } else if (l > 0 && temp == 3) {
                        tabs.push_back("  | L |  ");
                        l--;
                    } else {
                        // Trova la proprietà ancora disponibile
                        if (e > 0) {
                            tabs.push_back("  | E |  ");
                            e--;
                        } else if (s > 0) {
                            tabs.push_back("  | S |  ");
                            s--;
                        } else if (l > 0) {
                            tabs.push_back("  | L |  ");
                            l--;
                        }
                    }
            }
        }
    }
    if(p==1){
        tabs[corner_box1]="  | P |  ";
    }
    else if(p==2){
        tabs[corner_box2]="  | P |  ";
    }
    else if(p==3){
        tabs[corner_box3]="  | P |  ";
    }
    else{
        tabs[corner_box4]="  | P |  ";
    }
}

void tabellone::stampa(){
    static const int dim=10;
    std::string matrix[dim][dim];

    int a=0; 
    int b=27;
    int c=36;
    int d=44;
    int e=50;
    int f=58;

    // carica della matrice traimte vector
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(j==0){
                if(b<37){
                    matrix[i][j]=tabs[b++];
                }
            }
            else if(i==0){
                if(a<9){
                    matrix[i][j]=tabs[a++];
                }
            }
            else if(i==1){
                if(c<44){
                    if(c==36){
                        matrix[i][j]="  "+tabs[c++];
                    }
                    else{
                        matrix[i][j]=tabs[c++];
                    }
                }
            }
            else if(j==dim-2){
                if(d<50){
                    matrix[i][j]="                                                      "+tabs[d++];
                }
            }
            else if(i==dim-2){
                if(e==50){
                    matrix[i][j]="  "+tabs[e++];
                }
                else if(e<58){
                    matrix[i][j]=tabs[e++];
                }
            }
            else if(j==1){
                if(f<64){
                    matrix[i][j]="  "+tabs[f++];
                }
            }
        }
    }
    // stampa della matrice
    for(int i=0;i<dim-1;i++){
        for(int j=0;j<dim;j++){
            std::cout<<matrix[i][j];
        }
        std::cout<<std::endl;
    }
}