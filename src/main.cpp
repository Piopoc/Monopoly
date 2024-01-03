// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include <queue>
#include <fstream>
#include <memory>
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
    if(modalitaGioco != "computer" && modalitaGioco != "human"){
        cout << "Modalità non valida. Utilizzo: " << argv[0] << " <computer/human>" << endl;
        return 1;
    }   
    //creazione tabellone di gioco
    tabellone t;
    //creazione giocatori con 100 fiorini di budget
    Player p1 (1);
    Player p2 (2);
    Player p3 (3);
    Player p4 (4);
    //coda di gioco
    queue<Player*> pList;
    //vettore con lanci di dadi e corrispettivi giocatori
    vector<int> lanciDadi;
    vector<Player*> corrispettivi;
    lanciDadi.push_back(dice());
    corrispettivi.push_back(&p1);
    lanciDadi.push_back(dice());
    corrispettivi.push_back(&p2);
    lanciDadi.push_back(dice());
    corrispettivi.push_back(&p3);
    lanciDadi.push_back(dice());
    corrispettivi.push_back(&p4);
    cout<<lanciDadi[0]<<endl<<lanciDadi[1]<<endl<<lanciDadi[2]<<endl<<lanciDadi[3]<<endl;
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
    string ordine = "ordine di gioco:";
    for(int i =0; i<4; i++){
        Player* p = pList.front();
        int id = p->get_ID();
        pList.pop();
        pList.push(p);
        ordine += " p";
        ordine += to_string(id);
    }
    ordine += "\n";
    //apertura file log in scrittura
    ofstream ofs("../../monopoly/partita.log",ofstream::out);
    if(!ofs.good()) throw std::exception();
    cout<<ordine;
    ofs<<ordine;
    //inserisci i giocatori nella cella del via 
    t.start_game(&p1,&p2,&p3,&p4);
    cout<<" ___ ___   ___   ____    ___   ____    ___   _      ____      ____   __ __      _       ____  ___ ___  ____   ___     ____ "<<endl;
    cout<<"|   |   | /   \\ |    \\  /   \\ |    \\  /   \\ | |    |    |    |    \\ |  |  |    | |     /    ||   |   ||    \\ |   \\   /    |"<<endl;
    cout<<"| _   _ ||     ||  _  ||     ||  o  )|     || |     |  |     |  o  )|  |  |    | |    |  o  || _   _ ||  o  )|    \\ |  o  |"<<endl;
    cout<<"|  \\_/  ||  O  ||  |  ||  O  ||   _/ |  O  || |___  |  |     |     ||  ~  |    | |___ |     ||  \\_/  ||     ||  D  ||     |"<<endl;
    cout<<"|   |   ||     ||  |  ||     ||  |   |     ||     | |  |     |  O  ||___, |    |     ||  _  ||   |   ||  O  ||     ||  _  |"<<endl;
    cout<<"|   |   ||     ||  |  ||     ||  |   |     ||     | |  |     |     ||     |    |     ||  |  ||   |   ||     ||     ||  |  |"<<endl;
    cout<<"|___|___| \\___/ |__|__| \\___/ |__|    \\___/ |_____||____|    |_____||____/     |_____||__|__||___|___||_____||_____||__|__|"<<endl;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    //scelta modalità
    if (modalitaGioco == "computer") {
        //inizia la partita
        while(pList.size()!=1){
            //player del turno
            Player* pt = pList.front();
            pList.pop();
            int playerID = pt->get_ID();
            int initialPosition = pt->get_currpos();
            //sposto il giocatore
            int lancio = dice();
            ofs<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            t.move(pt,lancio); //?????????????????????????
            shared_ptr<Cell> currGenericCell = t.get_cell(pt->get_currpos());
            //situazioni possibili
            if(t.beyond_start(pt,initialPosition)){ //?????????????????????????
                pt->deposit(20);
                ofs<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato 20 fiorini"<<endl;
            }
            ofs<<"Giocatore "<<playerID<<" è arrivato alla casella "<<t.get_cellname(pt->get_currpos())<<endl;
            //casella angolare
            if(dynamic_pointer_cast<EdgeCell> (currGenericCell)){
                pList.push(pt);
                continue;
            }
            shared_ptr<SideCell> currCell = dynamic_pointer_cast<SideCell>(currGenericCell);
            //non ha proprietario, comprare?
            if(!currCell->has_owner()){
                int price = currCell->get_type().purchase_land;
                if(pt->pc_buys(price)){
                    pt->withdraw(price);
                    currCell->add_owner(pt);
                    ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<endl; //-...........
                }
                pList.push(pt);      
            }
            //pt è proprietario
            else if (currCell->get_owner()==pt){
                //proprietà senza casa, comprare casa?
                if(!currCell->has_house()){
                    int price = currCell->get_type().upgrade_to_house;
                    if(pt->pc_buys(price)){
                        pt->withdraw(price);
                        currCell->upgrade_property();
                        ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno"<<t.get_cellname(pt->get_currpos())<<endl;
                    }
                }
                //proprietà con casa, migliorare in hotel?
                if(currCell->has_house() && !currCell->has_hotel()){
                    int price = currCell->get_type().upgrade_to_hotel;
                    if(pt->pc_buys(price)){
                        pt->withdraw(price);
                        currCell->upgrade_property();
                        ofs<<"Giocatore "<<playerID<<"  ha migliorato una casa in albergo sul terreno"<<t.get_cellname(pt->get_currpos())<<endl; //stampa info terreno?
                    }
                }
                //proprietà con albergo non può fare niente
                pList.push(pt);
            }
            //proprietà altrui
            else{
                int tax = 0;
                if(currCell->has_house()){
                    tax = currCell->get_type().house_stay;
                }
                if(currCell->has_hotel()){
                    tax = currCell->get_type().hotel_stay;
                }
                //paga
                if(pt->has_this_money(tax)){
                    pt->withdraw(tax);
                    currCell->get_owner()->deposit(tax);
                    ofs<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<endl; //info su cell
                    pList.push(pt);
                }
                //non ha abbastanza soldi
                else{
                    t.elimination(pt);
                    ofs<<"Giocatore "<<playerID<<"è stato eliminato"<<endl;
                    //NON ESEGUO IL PUSH, eliminato giocatore
                }
            }
        }
        //termina la partita
        Player* winner = pList.front();
        ofs<<"Giocatore "<<winner->get_ID()<<" ha vinto la partita"<<endl;
        ofs.close();
    }
    else{ //(modalitaGioco == "human")
        t.print_matrix(); //ogni volta che viene richiesto
                    
        /*interazioni con humanPlayer
        arrivo su una casella non ancora venduta (chiede all’utente se desidera comprarla);
        arrivo su una casella di proprietà senza una casa (chiede all’utente se desidera costruire una casa);
        arrivo su una casella di proprietà con una casa (chiede all’utente se desidera migliorare la casa in albergo).
        */

        ofs.close();
    }
    return 0;
}