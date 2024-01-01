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
    Player* p1 = new Player(1);
    Player* p2 = new Player(2);
    Player* p3 = new Player(3);
    Player* p4 = new Player(4);
    //apertura file log in scrittura
    ofstream ofs("partita.log",ofstream::out);
    if(!ofs.good()) throw std::exception();
    //determinazione ordine di gioco inserendo i giocatori in una coda
    queue<Player*> pList;
    //vettore con lanci di dadi e corrispettivi giocatori
    vector<int> lanciDadi;
    vector<Player*> corrispettivi;
    lanciDadi.push_back(dice());
    corrispettivi.push_back(p1);
    lanciDadi.push_back(dice());
    corrispettivi.push_back(p2);
    lanciDadi.push_back(dice());
    corrispettivi.push_back(p3);
    lanciDadi.push_back(dice());
    corrispettivi.push_back(p4);
    //gestione ordine di partenza
    int full = 0;
    while(full!=4){
        if(!repeated_max(lanciDadi)){
            int posmax = get_posmax(lanciDadi);
            lanciDadi[posmax] = 0;
            pList.push(corrispettivi[posmax]);
            full++;
        }
        else{
            throw_again(lanciDadi);
        }
    }
    string ordine = "ordine di gioco:\n";
    for(int i =0; i<4; i++){
        Player* p = pList.front();
        int id = p->get_ID();
        pList.pop();
        pList.push(p);
        ordine += "p";
        ordine += id;
        ordine += "\n";
    }
    cout<<ordine;
    ofs<<ordine;
    //inserisci i giocatori nella cella del via 
    Cell* start = t.get_cell(0);
    start->add_occupant(p1);
    start->add_occupant(p2);
    start->add_occupant(p3);
    start->add_occupant(p4);
    //scelta modalità
    if (modalitaGioco == "computer") {
        //inizia la partita
        while(pList.size()!=1){
            //player del turno
            Player* pt = pList.front();
            pList.pop();
            int playerID = pt->get_ID();
            //sposto il giocatore
            int lancio = dice();
            ofs<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            t.move(pt,lancio); //?????????????????????????
            Cell* currGenericCell = t.get_cell(pt->get_currpos());
            //situazioni possibili
            if(passAcrossStart(player,fromCell,currGenericCell)){ //?????????????????????????
                pt->deposit(20);
                ofs<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato 20 fiorini"<<endl;
            }
            ofs<<"Giocatore "<<playerID<<" è arrivato alla casella "<<currCell; //cosa stampa il << di cell?//?????????????????????????
            //casella angolare
            if(dynamic_cast<EdgeCell*> (currGenericCell)){
                pList.push(pt);
                continue;
            }
            SideCell* currCell = currGenericCell;
            //non ha proprietario
            if(!currCell->has_owner()){
                if(pt->pc_buys(currCell->get_value())){
                    pt->withdraw(currCell->get_value());
                    currCell->add_owner(pt);
                    ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<currCell<<endl; //-...........
                }
                pList.push(pt);      
            }
            //pt è proprietario
            else if (currCell->get_owner()==pt){
                //proprietà senza casa
                if(!currCell->hasHouse()){
                    int price = currCell->get_type()->upgrade_to_house;
                    if(pt->pc_buys(price)){
                        currCell->add_owner(pt);
                        pt->withdraw(price);
                        ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno"<<currCell<<endl; //stampa info terreno?
                    }
                }
                //proprietà con casa
                if(currCell->hasHouse() && !currCell->hasAlbergo()){
                    int price = currCell->get_type()->upgrade_to_hotel;
                    if(pt->pc_buys(price)){
                        currCell->add_owner(pt);
                        pt->withdraw(price);
                        ofs<<"Giocatore "<<playerID<<"  ha migliorato una casa in albergo sul terreno"<<currCell<<endl; //stampa info terreno?
                    }
                }
                //proprietà con albergo non può fare niente
                pList.push(pt);
            }
            //proprietà altrui
            else{
                int tax = 0;
                if(currCell->has_house()){
                    tax = currCell->get_type()->house_stay;
                }
                if(currCell->has_hotel()){
                    tax = currCell->get_type()->hotel_stay;
                }
                //paga
                if(pt->has_this_money(tax)){
                    currCell->get_owner()->deposit(pt->withdraw(tax));
                    ofs<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<currCell<<endl; //info su cell
                    pList.push(pt);
                }
                //non ha abbastanza soldi
                else{
                    ofs<<"Giocatore "<<playerID<<"è stato eliminato"<<endl;
                    //NON ESEGUO IL PUSH, eliminato
                    //tutte le sue proprietà vengono rese libere
                    //t.elimination(pt);
                }
            }
        //termina la partita
        Player& winner = *pList.front();
        ofs<<"Giocatore "<<playerID<<" ha vinto la partita"<<endl;
        ofs.close();
        }
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