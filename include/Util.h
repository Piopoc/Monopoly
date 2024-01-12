// @author Alberto Levorato, matricola: 2066600

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <queue>
#include <fstream>
#include <memory>

#include "../include/Table.h"
#include "../include/Player.h"
#include "../include/Cell.h"

namespace util {
    void pc_plays(Table& t, Player* pt, std::shared_ptr<Cell> currGenericCell, std::queue<Player*>& pList, std::ofstream& ofs); //gestisce le azioni che il giocatore computer può fare all'interno della casella in cui si trova
    void human_plays(Table& t, Player* pt, std::shared_ptr<Cell> currGenericCell, std::queue<Player*>& pList, std::ofstream& ofs); //gestisce le azioni che il giocatore umano può fare all'interno della casella in cui si trova
    void game_over(std::queue<Player*>& pList, std::ofstream& ofs); //determina i vincitori e stampa il messaggio di vittoria
    void end_turn(Table& t, std::queue<Player*>& pList, Player* pt, bool pushPlayer); //gestisce il termine del turno del giocatore umano

    void show(Table& t, std::queue<Player*>& pList, Player* pt); //stampa il tabellone, la lista delle proprietà e i fiorini rimanenti a ciascun giocatore

    std::string put_in_order(std::queue<Player*>& pList); //mette in ordine con il criterio dei dadi
    bool repeated_max(std::vector<int>& a); //controlla se il lancio più alto ha un pareggio
    int get_posmax(std::vector<int>& a); //ottiene posizione del giocatore con punteggio massimo all'interno dell'array
    void throw_again(std::vector<int>& a, std::string& order); //rilancia i dadi massimi in pareggio
}
#endif