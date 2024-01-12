// @author Alberto Levorato, matricola: 2066600

#include <iostream>
#include <queue>
#include <fstream>
#include <memory>

#include "../include/Table.h"
#include "../include/Player.h"
#include "../include/Cell.h"
#include "../include/Util.h"

void util::human_plays(Table& t, Player* pt, std::shared_ptr<Cell> currGenericCell, std::queue<Player*>& pList, std::ofstream& ofs){
    std::string in;
    int playerID = pt->get_ID();
    //casella angolare
    if(std::dynamic_pointer_cast<EdgeCell> (currGenericCell)){
        std::cout<<"Si trova in una cella angolare"<<std::endl;
        end_turn(t, pList, pt, true);
        return;
    }
    std::shared_ptr<SideCell> currCell = std::dynamic_pointer_cast<SideCell>(currGenericCell);
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
            std::cout<<"Si trova in un terreno altrui, paga: "<<tax<<std::endl;
            pt->withdraw(tax);
            currCell->get_owner()->deposit(tax);
            ofs<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<std::endl;
            std::cout<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<std::endl;
            end_turn(t, pList, pt, true);
        }
        //non ha abbastanza soldi
        else{
            std::cout<<"Si trova in un terreno altrui, ma non possiede abbastanza denaro per pagare la tassa, viene eliminato"<<std::endl;
            currCell->get_owner()->deposit(pt->get_money());
            pt->withdraw(pt->get_money());
            t.elimination(pt);
            ofs<<"Giocatore "<<playerID<<" è stato eliminato"<<std::endl;
            std::cout<<"Giocatore "<<playerID<<" è stato eliminato"<<std::endl;
            //NON ESEGUO IL PUSH, eliminato giocatore
            end_turn(t, pList, pt, false);
        }
        return;
    }
    //pt è proprietario
    bool done = false;
    while(!done){
        //arrivo su una casella non ancora venduta (chiede all’utente se desidera comprarla);
        if(!currCell->has_owner()){
            int price = currCell->get_type().purchase_land;
            std::cout<<"Si trova in un terreno libero, desidera acquistare? Il prezzo è di "<<price<<" fiorini e ha a disposizione "<<pt->get_money()<<" fiorini\n[S]\n[N]\n[show]\n: ";
            std::getline(std::cin,in);
            if(in=="S" && pt->has_this_money(price)){
                pt->withdraw(price);
                currCell->add_owner(pt);
                ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                std::cout<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                done = true;
            }   
            else if(in=="S"){
                std::cout<<"Non possiede abbastanza denaro"<<std::endl;
                done = true;
            }
            else if(in=="N"){
                std::cout<<"Terreno non acquistato"<<std::endl;
                done = true;
            }
            else if(in=="show"){
                show(t,pList,pt);
            }
            else{
                std::cout<<"Comando non trovato"<<std::endl;
            }
        }
        //arrivo su una casella di proprietà senza una casa né hotel (chiede all’utente se desidera costruire una casa);
        else if(!currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_house;
            std::cout<<"Si trova in un suo terreno, desidera acquistare una casa? Il prezzo è di "<<price<<" fiorini e ha a disposizione "<<pt->get_money()<<" fiorini\n[S]\n[N]\n[show]\n: ";
            getline(std::cin,in);
            if(in=="S" && pt->has_this_money(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                std::cout<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                done = true;
            }   
            else if(in=="S"){
                std::cout<<"Non possiede abbastanza denaro"<<std::endl;
                done = true;
            }
            else if(in=="N"){
                std::cout<<"Casa non acquistata"<<std::endl;
                done = true;
            }
            else if(in=="show"){
                show(t,pList,pt);
            }
            else{
                std::cout<<"Comando non trovato"<<std::endl;
            }
        }
        //arrivo su una casella di proprietà con una casa (chiede all’utente se desidera migliorare la casa in albergo).
        else if(currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_hotel;
            std::cout<<"Si trova in un suo terreno con casa, desidera acquistare un albergo? Il prezzo è di "<<price<<" fiorini e ha a disposizione "<<pt->get_money()<<" fiorini\n[S]\n[N]\n[show]\n: ";
            getline(std::cin,in);
            if(in=="S" && pt->has_this_money(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<" ha migliorato una casa in albergo sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                std::cout<<"Giocatore "<<playerID<<" ha migliorato una casa in albergo sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                done = true;
            }   
            else if(in=="S"){
                std::cout<<"Non possiede abbastanza denaro"<<std::endl;
                done = true;
            }
            else if(in=="N"){
                std::cout<<"Hotel non acquistato"<<std::endl;
                done = true;
            }
            else if(in=="show"){
                show(t,pList,pt);
            }
            else{
                std::cout<<"Comando non trovato"<<std::endl;
            }
        }
        //proprietà con albergo non può fare niente
        else if(currCell->has_hotel()){
            std::cout<<"Si trova in una sua proprietà con albergo"<<std::endl;
            done = true;
        }
    }
    end_turn(t, pList, pt, true);
    return;
}
//
void util::pc_plays(Table& t, Player* pt, std::shared_ptr<Cell> currGenericCell, std::queue<Player*>& pList, std::ofstream& ofs){
    int playerID = pt->get_ID();
    //casella angolare
    if(std::dynamic_pointer_cast<EdgeCell> (currGenericCell)){
        pList.push(pt);
        return;
    }
    std::shared_ptr<SideCell> currCell = std::dynamic_pointer_cast<SideCell>(currGenericCell);
    //non ha proprietario, comprare?
    if(!currCell->has_owner()){
        int price = currCell->get_type().purchase_land;
        if(pt->pc_buys(price)){
            pt->withdraw(price);
            currCell->add_owner(pt);
            ofs<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
            std::cout<<"Giocatore "<<playerID<<" ha acquistato il terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
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
                ofs<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                std::cout<<"Giocatore "<<playerID<<" ha costruito una casa sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
            }
        }
        //proprietà con casa, migliorare in hotel?
        else if(currCell->has_house() && !currCell->has_hotel()){
            int price = currCell->get_type().upgrade_to_hotel;
            if(pt->pc_buys(price)){
                pt->withdraw(price);
                currCell->upgrade_property();
                ofs<<"Giocatore "<<playerID<<" ha migliorato una casa in albergo sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
                std::cout<<"Giocatore "<<playerID<<" ha migliorato una casa in albergo sul terreno "<<t.get_cellname(pt->get_currpos())<<std::endl;
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
            ofs<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<std::endl;
            std::cout<<"Giocatore "<<playerID<<" ha pagato "<<tax<<" fiorini a giocatore "<<currCell->get_owner()->get_ID()<<" per pernottamento nella casella "<<t.get_cellname(pt->get_currpos())<<std::endl;
            pList.push(pt);
        }
        //non ha abbastanza soldi
        else{
            currCell->get_owner()->deposit(pt->get_money());
            pt->withdraw(pt->get_money());
            t.elimination(pt);
            ofs<<"Giocatore "<<playerID<<" è stato eliminato"<<std::endl;
            std::cout<<"Giocatore "<<playerID<<" è stato eliminato"<<std::endl;
            //NON ESEGUO IL PUSH, eliminato giocatore
        }
    }
}
//
void util::game_over(std::queue<Player*>& pList, std::ofstream& ofs)
{
    if(pList.size()==1){
        Player* winner = pList.front();
        ofs<<"Giocatore "<<winner->get_ID()<<" ha vinto la partita"<<std::endl;
        std::cout<<"Giocatore "<<winner->get_ID()<<" ha vinto la partita"<<std::endl;
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
        std::vector<Player*> winners;
        for(int i = 0; i < pList.size(); i++){
            Player *p = pList.front();
            pList.pop();
            if(p->get_money()==max){
                winners.push_back(p);
            }
            pList.push(p);
        }
        //stampa messaggio
        std::cout<<"Giocator"<<((winners.size() == 1) ? "e " : "i ");
        ofs<<"Giocator"<<((winners.size() == 1) ? "e " : "i ");
        for(int i = 0; i < winners.size(); i++){
            std::cout<<winners[i]->get_ID()<<" ";
            ofs<<winners[i]->get_ID()<<" ";
        }
        std::cout<<((winners.size() == 1) ? "ha " : "hanno ")<<"vinto la partita per aver avuto il numero più alto di fiorini"<<std::endl;
        ofs<<((winners.size() == 1) ? "ha " : "hanno ")<<"vinto la partita per aver avuto il numero più alto di fiorini"<<std::endl;
    }
}
//
void util::end_turn(Table& t, std::queue<Player*>& pList, Player* pt, bool pushPlayer)
{
    bool done=false;
    std::string in;
    while(!done){
        std::cout<<"C per continuare oppure show \n[C]\n[show]\n: ";
        std::getline(std::cin,in);
        if(in=="C"){
            done=true;
        }
        else if(in=="show"){
            show(t,pList,pt);
        }
        else{
            std::cout<<"Comando non trovato"<<std::endl;
        }
    }

    if(pushPlayer){
        pList.push(pt);
    }
}
//
void util::show(Table& t, std::queue<Player*>& pList, Player* pt){
    std::cout<<std::endl<<"tabellone:"<<std::endl;
    t.print_matrix();
    std::cout<<std::endl<<"lista proprietà:"<<std::endl;
    t.list_property(pList,pt);
    std::cout<<std::endl<<"lista conti bancari:"<<std::endl;
    t.bank_account(pList,pt);
    std::cout<<std::endl;
}

std::string util::put_in_order(std::queue<Player*>& pList){
    std::vector<int> lanciDadi;
    std::vector<Player*> corrispettivi;
    std::string order;
    for(int i = 0; i<4; i++){
        lanciDadi.push_back(dice());
        order += "p" + std::to_string(i + 1) + " lancia i dadi e ottiene: " + std::to_string(lanciDadi[i]) + "\n";
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
            order += "turno " + std::to_string(full) + " p" + std::to_string(corrispettivi[posmax]->get_ID()) + "\n";
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
        order += " p" + std::to_string(id);
    }
    order += "\n";
    return order;
}

bool util::repeated_max(std::vector<int>& a){
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
int util::get_posmax(std::vector<int>& a){
    int max = 0;
    for(int i = 1; i<4; i++){
        if(a[i]>a[max]){
            max = i;
        }
    }
    return max;
}
void util::throw_again(std::vector<int>& a, std::string& order){
    int max = a[get_posmax(a)];
    for(int i = 0; i<4; i++){
        if(max!=0 && a[i]==max){
            a[i] = dice();
            order += "p" + std::to_string(i + 1) + " rilancia i dadi e ottiene: " + std::to_string(a[i]) + "\n";
        }
    }
}