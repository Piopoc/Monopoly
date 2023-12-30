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

    for(int i=0;i<dim;i++){
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
    int fraw=1;
    int fcolomn=65;

    int a=0; 
    int b=8;
    int c=21;
    int d=27;

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
            else if(i==1){
                if(a<8){
                    if(a==0){
                        matrix[i][j]="  "+tabs[a++];
                    }
                    else{
                        matrix[i][j]=tabs[a++];
                    }
                }
            }
            else if(j==dim-2){
                if(b<14){
                    matrix[i][j]="                                                      "+tabs[b++];
                }
            }
            else if(i==dim-2){
                if(c==21){
                    matrix[i][j]="  "+tabs[c--];
                }
                else if(c>=14){
                    matrix[i][j]=tabs[c--];
                }
            }
            else if(j==1){
                if(d>=21){
                    matrix[i][j]="  "+tabs[d--];
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
    std::cout<<std::endl;
// prova delle funzioni del mago --> chiedere a mago cosa scrivere nel parametro stringa
    EdgeCell pq(false,"abc");
    EdgeCell pq1(true,"abc");
    std::cout<<pq<<std::endl;
        //std::cout<<pq.to_string()<<std::endl;
    std::cout<<pq1<<std::endl;
    SideCell au(types::luxury(),"qr");
    std::cout<<au<<std::endl;
}