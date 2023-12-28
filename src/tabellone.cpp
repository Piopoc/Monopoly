// @author Filippo Corradi, matricola: 2066680

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/tabellone.h"


tabellone::tabellone(){
    srand(time(NULL));
    // random per casella di partenza
    int P=rand()%4+1;
    // numero massimo di proprietà economica, standard e lusso
    int E=8;
    int S=10;
    int L=6;
    // riga e colonna 0
    int a=64;
    int b=0;
    // carica della matrice vuota
    for(int i=0;i<getR();i++){
        for(int j=0;j<getC();j++){
            if(i>=1 && i<=8 && j>=1 && j<=8){
                tabs[i][j]="         ";
            }

            if ((i == 1 && j > 1 && j < 8) || (j == 1 && i > 1 && i < 8) || (i == 8 && j > 1 && j < 8) || (j == 8 && i > 1 && i < 8)) {
                if (E > 0 || S > 0 || L > 0) {
                    int temp = rand() % 3 + 1;

                    if (E > 0 && temp == 1) {
                        tabs[i][j] = "  | E |  ";
                        E--;
                    } else if (S > 0 && temp == 2) {
                        tabs[i][j] = "  | S |  ";
                        S--;
                    } else if (L > 0 && temp == 3) {
                        tabs[i][j] = "  | L |  ";
                        L--;
                    } else {
                        // Trova la proprietà ancora disponibile
                        if (E > 0) {
                            tabs[i][j] = "  | E |  ";
                            E--;
                        } else if (S > 0) {
                            tabs[i][j] = "  | S |  ";
                            S--;
                        } else if (L > 0) {
                            tabs[i][j] = "  | L |  ";
                            L--;
                        }
                    }
                } 
                // non entra mai in questo else (come è giusto che sia)
                else {
                    std::cout << "No resources available" << std::endl;
                }
            }
            // caselle angolari
            if((i==1 && j==1) || (i==1 && j==8) || (i==8 && j==1) || (i==8 && j==8)){
                tabs[i][j]="  |   |  ";
            }
            // colonna 0 dove assegno le lettere da A ad H
            if(j==0){
                tabs[i][j].assign(1,a++);
            }
            // riga 0 dove assegno i numeri da 1 ad 8
            if(i==0){
                tabs[i][j]="    "+std::to_string(b++)+"    ";
            }
            // spazio di tabulazione
            if(i==0 && j==0){
                tabs[i][j]=" ";
            }
        }
    }
    // casella di partenza in casella angolare random
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

const int tabellone::getC(){
    return colon;
}

const int tabellone::getR(){
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