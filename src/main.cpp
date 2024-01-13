// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include <queue>
#include <fstream>
#include <memory>

#include "../include/Table.h"
#include "../include/Player.h"
#include "../include/Cell.h"
#include "../include/Util.h"

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
    //creazione Table di gioco
    Table t;
    //tassa di passaggio da ritirare varcando il via
    constexpr int PASSTAX = 20;
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
    string order = util::put_in_order(pList);
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
            util::pc_plays(t,pt,currGenericCell,pList,ofs);
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
        util::game_over(pList, ofs);
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
                util::human_plays(t,pt,currGenericCell,pList,ofs);
                ofs<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
                cout<<"Giocatore "<<playerID<<" ha finito il turno"<<endl;
            }
            //giocatore computer
            else{
                util::pc_plays(t,pt,currGenericCell,pList,ofs);
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
        util::game_over(pList, ofs);
    }
    return 0;
}