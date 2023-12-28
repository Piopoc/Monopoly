#include <iostream>
#include "../include/tabellone.h"
#include "../include/player.h"
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
    tabellone t;
    Player p1;
    Player p2;
    Player p3;
    Player p4;
    
    if (modalitaGioco == "computer") {
        
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