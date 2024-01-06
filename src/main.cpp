// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include <queue>
#include <fstream>
#include <memory>
#include "../include/Table.h"
#include "../include/Player.h"
#include "../include/Cell.h"

using namespace std;

void pc_plays(Table& t, Player* pt, int playerID, shared_ptr<Cell> currGenericCell, queue<Player*>& pList, ostream& cout, ofstream& ofs);
void human_plays(Table& t, Player* pt, int playerID, shared_ptr<Cell> currGenericCell, queue<Player*>& pList, ostream& cout, ofstream& ofs);
void game_over(queue<Player*>& pList, ofstream& ofs);

void show(Table& t, queue<Player*>& pList);

string put_in_order(queue<Player*>& pList); //mette in ordine con il criterio dei dadi
bool repeated_max(vector<int>& a); //controlla se il lancio più alto ha un pareggio
int get_posmax(vector<int>& a); //ottiene posizione del giocatore con punteggio massimo all'interno dell'array
void throw_again(vector<int>& a, string& order); //rilancia i dadi massimi in pareggio

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
    //creazione Table di gioco
    Table t;
    //tassa di passaggio da ritirare varcando il via
    constexpr int PASSTAX = 5;
    //numero massimo di turni per partita con giocatore umano
    constexpr int MAX_ROUND_HUMAN = 500;
    //numero massimo di turni per partita con soli giocatori computer
    constexpr int MAX_ROUND_COMPUTER = 1000;
    //numero di turni
    int round = 0;
    //creazione giocatori con 100 fiorini di budget e id numerici
    Player p1 (1);
    Player p2 (2);
    Player p3 (3);
    Player p4 (4);
    //coda di gioco
    queue<Player*> pList;
    pList.push(&p1);
    pList.push(&p2);
    pList.push(&p3);
    pList.push(&p4);
    string order = put_in_order(pList);
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
    if (modalitaGioco == "computer") { //--------------------------------------------------------------------------------------------------------------------------------------------------------------
        //apertura file log in scrittura
        ofstream ofs("../../monopoly/computer.log",ofstream::out);
        if(!ofs.good()) throw std::exception();
        cout<<order;
        ofs<<order;
        //numero di giocatori che hanno giocato in questo round
        int havePlayed = 0;
        //numero di giocatori in gara all'inizio di ogni round
        int numberOfPlayers = pList.size();
        //inizia la partita
        while(pList.size()!=1 && round<MAX_ROUND_COMPUTER){
            //player del turno
            Player* pt = pList.front();
            pList.pop();
            int playerID = pt->get_ID();
            int initialPosition = pt->get_currpos();
            //sposto il giocatore
            int lancio = dice();
            ofs<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            cout<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            t.move(pt,lancio);
            shared_ptr<Cell> currGenericCell = t.get_cell(pt->get_currpos());
            //situazioni possibili
            if(t.beyond_start(pt,initialPosition)){
                pt->deposit(PASSTAX);
                ofs<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato "<<PASSTAX<<" fiorini"<<endl;
                cout<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato "<<PASSTAX<<" fiorini"<<endl;
            }
            ofs<<"Giocatore "<<playerID<<" è arrivato alla casella "<<t.get_cellname(pt->get_currpos())<<endl;
            cout<<"Giocatore "<<playerID<<" è arrivato alla casella "<<t.get_cellname(pt->get_currpos())<<endl;
            pc_plays(t,pt,playerID,currGenericCell,pList,cout,ofs);
            ofs<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
            cout<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
            //aumenta il numero di giocatori che hanno giocato per questo round
            havePlayed++;
            //se è uguale al numero di giocatori in gara, passa al round successivo 
            if(havePlayed == numberOfPlayers){
                havePlayed = 0;
                numberOfPlayers = pList.size();
                round++;
            }
        }
        //termina la partita
        game_over(pList, ofs);
    }
    else{ //(modalitaGioco == "human")
        //apertura file log in scrittura
        ofstream ofs("../../monopoly/human.log",ofstream::out);
        if(!ofs.good()) throw std::exception();
        cout<<order;
        ofs<<order;
        //numero di giocatori che hanno giocato in questo round
        int havePlayed = 0;
        //numero di giocatori in gara all'inizio di ogni round
        int numberOfPlayers = pList.size();
        int humanID = pList.front()->get_ID();
        //inizia la partita
        while(pList.size()!=1 && round<MAX_ROUND_HUMAN){
            //player del turno
            Player* pt = pList.front();
            pList.pop();
            int playerID = pt->get_ID();
            int initialPosition = pt->get_currpos();
            //sposto il giocatore
            int lancio = dice();
            ofs<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            cout<<"Giocatore "<<playerID<<" ha tirato i dadi ottenendo un valore di "<<lancio<<endl;
            t.move(pt,lancio);
            shared_ptr<Cell> currGenericCell = t.get_cell(pt->get_currpos());
            //situazioni possibili
            if(t.beyond_start(pt,initialPosition)){
                pt->deposit(PASSTAX);
                ofs<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato "<<PASSTAX<<" fiorini"<<endl;
                cout<<"Giocatore "<<playerID<<" è passato dal via e ha ritirato "<<PASSTAX<<" fiorini"<<endl;
            }
            ofs<<"Giocatore "<<playerID<<" è arrivato alla casella "<<t.get_cellname(pt->get_currpos())<<endl;
            cout<<"Giocatore "<<playerID<<" è arrivato alla casella "<<t.get_cellname(pt->get_currpos())<<endl;
            if(pt->get_ID()==humanID){
                human_plays(t,pt,playerID,currGenericCell,pList,cout,ofs);
                ofs<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
                cout<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
            }
            //giocatore computer
            else{
                pc_plays(t,pt,playerID,currGenericCell,pList,cout,ofs);
                ofs<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
                cout<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
            }
            //aumenta il numero di giocatori che hanno giocato per questo round
            havePlayed++;
            //se è uguale al numero di giocatori in gara, passa al round successivo 
            if(havePlayed == numberOfPlayers){
                havePlayed = 0;
                numberOfPlayers = pList.size();
                round++;
            }
        }
        //termina la partita
        game_over(pList, ofs);
    }
    return 0;
} //------------------------------------------------------------------------------------------------------------------------------------------------
//
void human_plays(Table& t, Player* pt, int playerID, shared_ptr<Cell> currGenericCell, queue<Player*>& pList, ostream& cout, ofstream& ofs){
    string in;
    //casella angolare
    if(dynamic_pointer_cast<EdgeCell> (currGenericCell)){
        pList.push(pt);
        cout<<"Si trova in una cella angolare"<<endl;
        return;
    }
    shared_ptr<SideCell> currCell = dynamic_pointer_cast<SideCell>(currGenericCell);
    //proprietà altrui
    if(currCell->has_owner() && currCell->get_owner()!=pt){
        int tax = 0;
        if(currCell->has_house()){
            tax = currCell->get_type().house_stay;
        }
        if(currCell->has_hotel()){
            tax = currCell->get_type().hotel_stay;
        }
        //paga
        if(pt->has_this_money(tax)){
            cout<<"Si trova in un terreno altrui, paga: "<<tax<<endl;
            pt->withdraw(tax);
            currCell->get_owner()->deposit(tax);
            ofs<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<endl;
            cout<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<endl;
            pList.push(pt);
            return;
        }
        //non ha abbastanza soldi
        else{
            cout<<"Si trova in un terreno altrui, ma non possiede abbastanza denaro per pagare la tassa, viene eliminato"<<endl;
            t.elimination(pt);
            ofs<<"Giocatore "<<playerID<<" è stato eliminato"<<endl;
            cout<<"Giocatore "<<playerID<<" è stato eliminato"<<endl;
            //NON ESEGUO IL PUSH, eliminato giocatore
            return;
        }
    }
    //pt è proprietario
    bool done = false;
    while(!done){
        //arrivo su una casella non ancora venduta (chiede all’utente se desidera comprarla);
        if(!currCell->has_owner()){
            int price = currCell->get_type().purchase_land;
            cout<<"Si trova in un terreno libero, desidera acquistare? Il prezzo è di "<<price<<" fiorini e ha a disposizione "<<pt->get_money()<<" fiorini\n[S]\n[N]\n[show]\n: ";
            std::getline(cin,in);
            if(in=="S" && pt->has_this_money(price)){
                pt->withdraw(price);
                currCell->add_owner(pt);
                ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<endl;
                cout<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<endl;
                pList.push(pt);
                done = true;
            }   
            else if(in=="S"){
                cout<<"Non possiede abbastanza denaro"<<endl;
                pList.push(pt);
                done = true;
            }
            else if(in=="N"){
                cout<<"Terreno non acquistato"<<endl;
                pList.push(pt);
                done = true;
            }
            else if(in=="show"){
                show(t,pList);
            }
            else{
                cout<<"Comando non trovato"<<endl;
            }
        }
        //arrivo su una casella di proprietà senza una casa né hotel (chiede all’utente se desidera costruire una casa);
        if(!currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_house;
            cout<<"Si trova in un suo terreno, desidera acquistare una casa? Il prezzo è di "<<price<<" fiorini e ha a disposizione "<<pt->get_money()<<" fiorini\n[S]\n[N]\n[show]\n: ";
            getline(cin,in);
            if(in=="y" && pt->has_this_money(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno"<<t.get_cellname(pt->get_currpos())<<endl;
                cout<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno"<<t.get_cellname(pt->get_currpos())<<endl;
                pList.push(pt);
                done = true;
            }   
            else if(in=="S"){
                cout<<"Non possiede abbastanza denaro"<<endl;
                pList.push(pt);
                done = true;
            }
            else if(in=="N"){
                cout<<"Casa non acquistata"<<endl;
                pList.push(pt);
                done = true;
            }
            else if(in=="show"){
                show(t,pList);
            }
            else{
                cout<<"Comando non trovato"<<endl;
            }
        }
        //arrivo su una casella di proprietà con una casa (chiede all’utente se desidera migliorare la casa in albergo).
        if(currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_hotel;
            cout<<"Si trova in un suo terreno con casa, desidera acquistare un albergo? Il prezzo è di "<<price<<" fiorini e ha a disposizione "<<pt->get_money()<<" fiorini\n[y]\n[n]\n[show]\n: ";
            getline(cin,in);
            if(in=="y" && pt->has_this_money(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<"  ha migliorato una casa in albergo sul terreno"<<t.get_cellname(pt->get_currpos())<<endl;
                cout<<"Giocatore "<<playerID<<"  ha migliorato una casa in albergo sul terreno"<<t.get_cellname(pt->get_currpos())<<endl;
                pList.push(pt);
                done = true;
            }   
            else if(in=="y"){
                cout<<"Non possiede abbastanza denaro"<<endl;
                pList.push(pt);
                done = true;
            }
            else if(in=="n"){
                cout<<"Hotel non acquistato"<<endl;
                pList.push(pt);
                done = true;
            }
            else if(in=="show"){
                show(t,pList);
            }
            else{
                cout<<"Comando non trovato"<<endl;
            }
        }
        //proprietà con albergo non può fare niente
        if(currCell->has_hotel()){
            cout<<"Si trova in una sua proprietà con albergo"<<endl;
            pList.push(pt);
            done = true;
        }
    }
    return;
}
//
void pc_plays(Table& t, Player* pt, int playerID, shared_ptr<Cell> currGenericCell, queue<Player*>& pList, ostream& cout, ofstream& ofs){
    //casella angolare
    if(dynamic_pointer_cast<EdgeCell> (currGenericCell)){
        pList.push(pt);
        return;
    }
    shared_ptr<SideCell> currCell = dynamic_pointer_cast<SideCell>(currGenericCell);
    //non ha proprietario, comprare?
    if(!currCell->has_owner()){
        int price = currCell->get_type().purchase_land;
        if(pt->pc_buys(price)){
            pt->withdraw(price);
            currCell->add_owner(pt);
            ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<endl;
            cout<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<endl;
        }
        pList.push(pt);      
    }
    //pt è proprietario
    else if (currCell->get_owner()==pt){
        //proprietà senza casa, comprare casa?
        if(!currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_house;
            if(pt->pc_buys(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno "<<t.get_cellname(pt->get_currpos())<<endl;
                cout<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno "<<t.get_cellname(pt->get_currpos())<<endl;
            }
        }
        //proprietà con casa, migliorare in hotel?
        if(currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_hotel;
            if(pt->pc_buys(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<" ha migliorato una casa in albergo sul terreno "<<t.get_cellname(pt->get_currpos())<<endl;
                cout<<"Giocatore "<<playerID<<" ha migliorato una casa in albergo sul terreno "<<t.get_cellname(pt->get_currpos())<<endl;
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
            ofs<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<endl;
            cout<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<endl;
            pList.push(pt);
        }
        //non ha abbastanza soldi
        else{
            t.elimination(pt);
            ofs<<"Giocatore "<<playerID<<" è stato eliminato"<<endl;
            cout<<"Giocatore "<<playerID<<" è stato eliminato"<<endl;
            //NON ESEGUO IL PUSH, eliminato giocatore
        }
    }
}
//
void game_over(queue<Player*>& pList, ofstream& ofs)
{
    if(pList.size()==1){
        Player* winner = pList.front();
        ofs<<"Giocatore "<<winner->get_ID()<<" ha vinto la partita"<<endl;
        cout<<"Giocatore "<<winner->get_ID()<<" ha vinto la partita"<<endl;
    }
    else{
        //determina qual è il numero più alto di fiorini
        int max = 0;
        for(int i = 0; i < pList.size(); i++){
            Player *p = pList.front();
            pList.pop();
            if(p->get_money()>max){
                max = p->get_money();
            }
            pList.push(p);
        }
        //determina quali sono i giocatori aventi numero di fiorini pari a max
        vector<Player*> winners;
        for(int i = 0; i < pList.size(); i++){
            Player *p = pList.front();
            pList.pop();
            if(p->get_money()==max){
                winners.push_back(p);
            }
            pList.push(p);
        }
        //stampa messaggio
        cout<<"Giocator"<<((winners.size() == 1) ? "e " : "i ");
        ofs<<"Giocator"<<((winners.size() == 1) ? "e " : "i ");
        for(int i = 0; i < winners.size(); i++){
            cout<<winners[i]->get_ID()<<" ";
            ofs<<winners[i]->get_ID()<<" ";
        }
        cout<<((winners.size() == 1) ? "ha " : "hanno ")<<"vinto la partita per aver avuto il numero più alto di fiorini"<<endl;
        ofs<<((winners.size() == 1) ? "ha " : "hanno ")<<"vinto la partita per aver avuto il numero più alto di fiorini"<<endl;
    }
}
//
void show(Table& t, queue<Player*>& pList){
    cout<<endl<<"tabellone:"<<endl;
    t.print_matrix();
    cout<<endl<<"lista proprietà:"<<endl;
    t.list_property(pList);
    cout<<endl<<"lista conti bancari:"<<endl;
    t.bank_account(pList);
    cout<<endl;
}

string put_in_order(queue<Player*>& pList){
    vector<int> lanciDadi;
    vector<Player*> corrispettivi;
    string order;
    for(int i = 0; i<4; i++){
        lanciDadi.push_back(dice());
        order += "p" + to_string(i + 1) + " lancia i dadi e ottiene: " + to_string(lanciDadi[i]) + "\n";
        Player* p = pList.front();
        corrispettivi.push_back(p);
        pList.pop();
    }

    order += "ordine di gioco:\n";
    int full = 0;
    while(full!=4){
        if(!repeated_max(lanciDadi)){
            int posmax = get_posmax(lanciDadi);
            lanciDadi[posmax] = 0;
            pList.push(corrispettivi[posmax]);
            full++;
            order += "turno " + to_string(full) + " p" + to_string(corrispettivi[posmax]->get_ID()) + "\n";
        }
        else{
            throw_again(lanciDadi,order);
        }
    }

    for(int i =0; i<4; i++){
        Player* p = pList.front();
        int id = p->get_ID();
        pList.pop();
        pList.push(p);
        order += " p" + to_string(id);
    }
    order += "\n";
    return order;
}

bool repeated_max(vector<int>& a){
    int max = a[get_posmax(a)];
    bool done = false;
    for(int i = 0; i<4; i++){
        if(max!=0 && a[i]==max){
            if(done){
                return true;
            }
            done = true;
        }
    }
    return false;
}
int get_posmax(vector<int>& a){
    int max = 0;
    for(int i = 1; i<4; i++){
        if(a[i]>a[max]){
            max = i;
        }
    }
    return max;
}
void throw_again(vector<int>& a, string& order){
    int max = a[get_posmax(a)];
    for(int i = 0; i<4; i++){
        if(max!=0 && a[i]==max){
            a[i] = dice();
            order += "p" + to_string(i + 1) + " rilancia i dadi e ottiene: " + to_string(a[i]) + "\n";
        }
    }
}