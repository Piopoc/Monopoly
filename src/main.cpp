// @author Alberto Levorato, matricola: 2066600

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
    Player* p1;
    Player* p2;
    Player* p3;
    Player* p4;
    /*  //apertura file log in scrittura
    ofstream ofs("partita.log",ofstream::out);
    if(!ofs.good()) throw std::exception();
    //determinazione ordine di gioco inserendo i giocatori in una coda
    queue<Player*> pList; //da valutare se mettere nel free store
    //vettore con lanci di dadi e corrispettivi giocatori
    vector<int> lanciDadi;
    vector<Player*> corrispettivi;
    lanciDadi.push_back(dadi());
    corrispettivi.push_back(p1);
    lanciDadi.push_back(dadi());
    corrispettivi.push_back(p2);
    lanciDadi.push_back(dadi());
    corrispettivi.push_back(p3);
    lanciDadi.push_back(dadi());
    corrispettivi.push_back(p4);
    
    //gestione ordine di partenza
    int full = 0;
    while(full!=4){
        if(noMaxRipetuti(lanciDadi)){
            int posMax = getPosMax(lanciDadi);
            lanciDadi[posMax] = 0;
            pList.push(corrispettivi[posMax]);
            full++;
        }
        else{
            rilanciaMaxRipetuti(lanciDadi);
        }
    }
    //ordine di gioco
    string ordine = "ordine di gioco:\n";
    for(int i =0; i<4; i++){
        Player* p = pList.front();
        Player& pref = *p;
        int id = pref.getID();
        pList.pop();
        pList.push(p);
        ordine += "p";
        ordine += id;
        ordine += "\n";
    }
    cout<<ordine;
    ofs<<ordine; */
    //inserisci i giocatori nella cella del via
    //t.insertStart(p1);
    //t.insertStart(p2);
    //t.insertStart(p3);
    //t.insertStart(p4);
    
    if (modalitaGioco == "computer") {/*
    while(pList.size()!=1){
        Player* p = pList.front();
        Player& pt = *p; //player del turno
        pList.pop();
        int lancio = dadi();
        int playerID = pt.getID();
        ofs<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
        Cell fromCell = t.whereIs(pt);
        Cell currCell = t.whereIs(pt);
        t.move(pt,fromCell,lancio);
        if(passAcrossStart(player,fromCell,currCell)){
            pt.versa(20);
            ofs<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato 20 fiorini"<<endl;
        }
        ofs<<"Giocatore "<<playerID<<" è arrivato alla casella "<<currCell; //cosa stampa il << di cell?
        if(dynamic_cast<EdgeCell*> (currCell)){
            pList.push(p);
        }
        else if(currCell.getOwner()==nullptr){
            if(pt.computerCompra(currCell.get_value())){
                pt.preleva(currCell.get_value());
                currCell.setProp(pt);
                ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<currCell<<endl; //-...........
            }
            pList.push(p);      
        }
        else if (currCell.getOwner()==pt){
            if(!currCell.hasHouse()){
                if(pt.computerCompra(currCell.get_value())){
                //valutare il prezzo in base al terreno
                pt.preleva(prezzo);
                ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno"<<currCell<<endl; //stampa info terreno?
                }
            }
            if(!currCell.hasAlbergo()){ //Casella di proprietà con casa
                if(pt.computerCompra(currCell.get_value())){
                int prezzo; //valutare il prezzo in base al terreno
                pt.preleva(prezzo);
                ofs<<"Giocatore "<<playerID<<"  ha migliorato una casa in albergo sul terreno"<<currCell<<endl; //stampa info terreno?
                }
            }
            pList.push(p);
        }
        else{ //Casella laterale con casa/albergo proprietà altrui
            int valoreProp = currCell.get_value();
            if(pt.hasThisMoney(valoreProp)){
                currCell.getProprietario().versa(pt.preleva(valoreProp));
                ofs<<<<"Giocatore "<<playerID<<" ha pagato "<<valoreProp<<" fiorini a giocatore "<<currCell.getProprietario().getID()<<" per pernottamento nella casella "<<currCell<<endl; //info su cell
                pList.push(p);
            }
            else{ //non ha abbastanza soldi
                ofs<<"Giocatore "<<playerID<<"è stato eliminato"<<endl;
                //NON ESEGUO IL PUSH, eliminato
                //tutte le sue proprietà vengono rese libere
            }
        }
        Player& winner = *pList.front();
        ofs<<"Giocatore "<<playerID<<" ha vinto la partita"<<endl;*/
        //ofs.close();
    }
    else if (modalitaGioco == "human") {
    t.stampa(); //ogni volta che viene richiesto
                
    /*interazioni con humanPlayer
    arrivo su una casella non ancora venduta (chiede all’utente se desidera comprarla);
    arrivo su una casella di proprietà senza una casa (chiede all’utente se desidera costruire una casa);
    arrivo su una casella di proprietà con una casa (chiede all’utente se desidera migliorare la casa in albergo).
    */

    //ofs.close();
    }
    else {
        cout << "Modalità non valida. Utilizzo: " << argv[0] << " <computer/human>" << endl;
        //ofs << "Modalità non valida. Utilizzo: " << argv[0] << " <computer/human>" << endl;
        //ofs.close();
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
    */ return 0;

}