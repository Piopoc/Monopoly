// @author Filippo Corradi, matricola: 2066680

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/tabellone.h"

tabellone::tabellone(){
    srand(time(NULL));
    // random per casella di partenza
    int P=rand()%4+1;
    int a=64;
    int b=0;
    for(int i=0;i<getR();i++){
        for(int j=0;j<getC();j++){
            if(i>1 || i<8 || j>1 || j<8){
                tabs[i][j]="         ";
            }
            if(i==1 || j==1 || i==8 || j==8){
                // questo va' modificato con l'estrazione del tipo delle caselle laterali
                tabs[i][j]="  |   |  ";
            }
            if((i==1&&j==1)||(i==1&&j==8)||(i==8&&j==1)||(i==8&&j==8)){
                tabs[i][j]="  |   |  ";
            }
            if(j==0){
                tabs[i][j].assign(1,a++);
            }
            if(i==0){
                tabs[i][j]="    "+std::to_string(b++)+"    ";
            }
            if(i==0 && j==0){
                tabs[i][j]=" ";
            }
        }
    }
    if(P==1){
        tabs[1][1]="  | P |  ";
    }
    else if(P==2){
        tabs[1][8]="  | P |  ";
    }
    else if(P==3){
        tabs[8][1]="  | P |  ";
    }
    else{
        tabs[8][8]="  | P |  ";
    }
}

int tabellone::getC(){
    return colon;
}

int tabellone::getR(){
    return righe;
}

void tabellone::stampa() {
    for (int i = 0; i < getR(); ++i) {
        for (int j = 0; j < getC(); ++j) {
            std::cout << tabs[i][j];
        }
        std::cout << std::endl;
    }
}