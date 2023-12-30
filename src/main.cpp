#include <iostream>
#include <queue>
#include <fstream>
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
    //creazione tabellone di gioco
    tabellone t;
    //creazione giocatori con 100 fiorini di budget
    Player p1;
    Player p2;
    Player p3;
    Player p4;

    //tirare i dadi per stabilire chi sarà il primo a partire

    //determinazione ordine di gioco inserendo i giocatori in
    //una coda e la scorriamo man mano per ogni turno
    //finche non termina la partita quando la coda ha solo 1 giocatore
    queue<Player> pList; //da valutare se mettere nel free store
    pList.push(p1);
    pList.push(p2);
    pList.push(p3);
    pList.push(p4);
    
    if (modalitaGioco == "computer") {
        std::ofstream ofs("computer.log",ofstream::out);
        if(!ofs.good()) throw std::exception();

        while(pList.size()!=1){
            Player& pt = pList.front(); //player del turno
            pList.pop();
            int lancio = dadi();
            int playerID = pt.getID();
            ofs<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            //t.move(pt,lancio);
            //Cell currCell = get_pos();
                //if(passaggio per il via)
                    ofs<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato 20 fiorini"<<endl;
            //ofs<<"Giocatore "<<playerID<<" è arrivato alla casella "<<currCell; //cosa stampa il << di cell?
                //if(currCell.isCasellaAngolare())
                    //pList.push(pt);
                //else if (currCell.isLaterale() && currCell.noProprietario())
                    //if(pt.computerCompra(currCell.get_value()))
                        //pt.preleva(currCell.get_value());
                        //currCell.setProp(pt);
                        //ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<currCell<<endl; //-...........
                    
                //else if (currCell.isLaterale() &&  currCell.Proprietario()==pt && currCell.noEdifici())
                    //if(pt.computerCompra(currCell.get_value()))
                        //valutare il prezzo in base al terreno
                        //pt.preleva(prezzo);
                        //ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno"<<currCell<<endl; //stampa info terreno?
                //else if (currCell.isLaterale() &&  currCell.Proprietario()==pt && currCell.c'èCasa())
                    //if(pt.computerCompra(currCell.get_value()))
                        //valutare il prezzo in base al terreno
                        //pt.preleva(prezzo);
                        //ofs<<"Giocatore "<<playerID<<"  ha migliorato una casa in albergo sul terreno"<<currCell<<endl; //stampa info terreno?
                //else //Casella laterale con casa/albergo proprietà altrui
                    //int valoreProp = currCell.get_value();
                    //if(pt.hasThisMoney(valoreProp))
                        //currCell.getProprietario().versa(pt.preleva(valoreProp));
                        //ofs<<<<"Giocatore "<<playerID<<" ha pagato "<<valoreProp<<" fiorini a giocatore "<<currCell.getProprietario().getID()<<" per pernottamento nella casella "<<currCell<<endl; //info su cell
                        pList.push(pt);
                    //else //non ha abbastanza soldi
                        ofs<<"Giocatore "<<playerID<<"è stato eliminato"<<endl;
                        //NON ESEGUO IL PUSH, eliminato
                        //tutte le sue proprietà vengono rese libere
        }
        Player& winner = pList.front();
        //ofs<<"Giocatore "<<playerID<<" ha vinto la partita"<<endl;

        ofs.close();
    } else if (modalitaGioco == "human") {
        //giocaUmano();
        t.stampa(); //ogni volta che viene richiesto
    } else {
        cout << "Modalità non valida. Utilizzo: " << argv[0] << " <computer/human>" << endl;
        return 1;
    }

    
    /* cout<<" ___ ___   ___   ____    ___   ____    ___   _      ____      ____   __ __      _       ____  ___ ___  ____   ___     ____ "<<endl;
    cout<<"|   |   | /   \\ |    \\  /   \\ |    \\  /   \\ | |    |    |    |    \\ |  |  |    | |     /    ||   |   ||    \\ |   \\   /    |"<<endl;
    cout<<"| _   _ ||     ||  _  ||     ||  o  )|     || |     |  |     |  o  )|  |  |    | |    |  o  || _   _ ||  o  )|    \\ |  o  |"<<endl;
    cout<<"|  \\_/  ||  O  ||  |  ||  O  ||   _/ |  O  || |___  |  |     |     ||  ~  |    | |___ |     ||  \\_/  ||     ||  D  ||     |"<<endl;
    cout<<"|   |   ||     ||  |  ||     ||  |   |     ||     | |  |     |  O  ||___, |    |     ||  _  ||   |   ||  O  ||     ||  _  |"<<endl;
    cout<<"|   |   ||     ||  |  ||     ||  |   |     ||     | |  |     |     ||     |    |     ||  |  ||   |   ||     ||     ||  |  |"<<endl;
    cout<<"|___|___| \\___/ |__|__| \\___/ |__|    \\___/ |_____||____|    |_____||____/     |_____||__|__||___|___||_____||_____||__|__|"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
 */

    return 0;
}