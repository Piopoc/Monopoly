#include <iostream>
#include "../include/tabellone.h"

using namespace std;

int main(int argc, char* argv[]){

    if (argc != 2) {
        cout << "Utilizzo: " << argv[0] << " <computer/human>" << endl;
        return -1; // restituisco 1 per indicare un errore
    }
    string modalitaGioco = argv[1];
    srand(static_cast<unsigned int>(time(0)));

    if (modalitaGioco == "computer") {
        //giocaComputer();
    } else if (modalitaGioco == "human") {
        //giocaUmano();
    } else {
        cout << "Modalità non valida. Utilizzo: " << argv[0] << " <computer/human>" << endl;
        return 1;
    }

    tabellone t;
    cout<<"  .___  ___.   ______   .__   __.   ______   .______     ______    __       __     .______   ____    ____     __           ___      .___  ___. .______    _______       ___      "<<endl;
    cout<<"  |   \\/   |  /  __  \\  |  \\ |  |  /  __  \\  |   _  \\   /  __  \\  |  |     |  |    |   _  \\  \\   \\  /   /    |  |         /   \\     |   \\/   | |   _  \\  |       \\     /   \\     "<<endl;
    cout<<"  |  \\  /  | |  |  |  | |   \\|  | |  |  |  | |  |_)  | |  |  |  | |  |     |  |    |  |_)  |  \\   \\/   /     |  |        /  ^  \\    |  \\  /  | |  |_)  | |  .--.  |   /  ^  \\    "<<endl;
    cout<<"  |  |\\/|  | |  |  |  | |  . `  | |  |  |  | |   ___/  |  |  |  | |  |     |  |    |   _  <    \\_    _/      |  |       /  /_\\  \\   |  |\\/|  | |   _  <  |  |  |  |  /  /_\\  \\   "<<endl;
    cout<<"  |  |  |  | |  `--'  | |  |\\   | |  `--'  | |  |      |  `--'  | |  `----.|  |    |  |_)  |     |  |        |  `----. /  _____  \\  |  |  |  | |  |_)  | |  '--'  | /  _____  \\  "<<endl;
    cout<<"  |__|  |__|  \\______/  |__| \\__|  \\______/  | _|       \\______/  |_______||__|    |______/      |__|        |_______|/__/     \\__\\ |__|  |__| |______/  |_______/ /__/     \\__\\ "<<endl<<endl<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    t.stampa();


    return 0;
}