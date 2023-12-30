#include <iostream>
#include "../include/tabellone.h"
#include "../include/Player.h"
#include "../include/Cell.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc != 2) {
        cout << "Utilizzo: " << argv[0] << " <computer/human>" << endl;
        return -1; // restituisco 1 per indicare un errore
    }
    string modalitaGioco = argv[1];
    srand(static_cast<unsigned int>(time(0)));
    int conta_player=4;
    // se player non ha soldi viene eliminato --> diminuisco il conta_player (se è uguale a 1, il player rimanente ha vinto)
    
    //creazione tabellone di gioco
    tabellone t;
    //creazione giocatori con 100 fiorini di budget
    Player p1;
    Player p2;
    Player p3;
    Player p4;

    //tirare i dadi per stabilire chi sarà il primo a partire

    //determinazione ordine di gioco
    //idea mettiamo i 4 player in unarray circolare e lo scorriamo
    //all'infinito per girare i turni finche non termina la partita
    
    if (modalitaGioco == "computer") {
        //while(larray circolare ha pi' di un elemento)
            //giocatore del turno tira i dadi
            //cout<<Giocatore N ha tirato i dadi ottenendo un valore di X
            //muovi pedina
                //if(passaggio per il via)
                    //cout<<Giocatore N è passato dal via e ha ritirato 20 fiorini
            //cout<<Giocatore N è arrivato alla casella Y
                //if(casella angolare)
                //else if (Casella laterale non appartenente nessuno dei giocatori)
                    //if(compra)
                        //cout<<Giocatore N ha acquistato il terreno Y
                //else if (Casella laterale di proprietà giocatore, senza casa/albergo)
                    //if(costruisce casa)
                        //cout<<Giocatore N ha costruito una casa sul terreno Y
                //else if (Casella laterale con casa proprietà)
                    //if(migliora in albergo)
                        //cout<<Giocatore N ha migliorato una casa in albergo sul terreno Y
                //else (Casella laterale con casa proprietà)
                    //if(paga)
                        //cout<<Giocatore N ha pagato Z fiorini a giocatore M per pernottamento nella casella Y
                    //else(non ha soldi)
                        //cout<<Giocatore N è stato eliminato
                        //eliminato (tolgo da array e ridimensiono)
                        //tutte le sue proprietà vengono rese libere
            //cout<<Giocatore N ha vinto la partita
    } else if (modalitaGioco == "human") {
        //giocaUmano();
    } else {
        cout << "Modalità non valida. Utilizzo: " << argv[0] << " <computer/human>" << endl;
        return 1;
    }

    
    cout<<" ___ ___   ___   ____    ___   ____    ___   _      ____      ____   __ __      _       ____  ___ ___  ____   ___     ____ "<<endl;
    cout<<"|   |   | /   \\ |    \\  /   \\ |    \\  /   \\ | |    |    |    |    \\ |  |  |    | |     /    ||   |   ||    \\ |   \\   /    |"<<endl;
    cout<<"| _   _ ||     ||  _  ||     ||  o  )|     || |     |  |     |  o  )|  |  |    | |    |  o  || _   _ ||  o  )|    \\ |  o  |"<<endl;
    cout<<"|  \\_/  ||  O  ||  |  ||  O  ||   _/ |  O  || |___  |  |     |     ||  ~  |    | |___ |     ||  \\_/  ||     ||  D  ||     |"<<endl;
    cout<<"|   |   ||     ||  |  ||     ||  |   |     ||     | |  |     |  O  ||___, |    |     ||  _  ||   |   ||  O  ||     ||  _  |"<<endl;
    cout<<"|   |   ||     ||  |  ||     ||  |   |     ||     | |  |     |     ||     |    |     ||  |  ||   |   ||     ||     ||  |  |"<<endl;
    cout<<"|___|___| \\___/ |__|__| \\___/ |__|    \\___/ |_____||____|    |_____||____/     |_____||__|__||___|___||_____||_____||__|__|"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    t.stampa();


    return 0;
}