#include <iostream>
#include "../include/tabellone.h"

tabellone::tabellone(){
    int a=64;
    int b=0;
    for(int i=0;i<getR();i++){
        for(int j=0;j<getC();j++){
            if(i>1 || i<8 || j>1 || j<8){
                tabs[i][j]="         ";
            }
            if(i==1 || j==1 || i==8 || j==8){
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