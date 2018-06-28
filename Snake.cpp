//
// Created by nils on 27/06/18.
//

#include "Snake.h"

Snake::Snake(int p_nb, int id) : nb_players(p_nb), id(id) {
}

void Snake::addHead(int X0, int Y0, int X1, int Y1, int id_head) {
    if (X0 == -1)
        map.removeDeadPlayers(id_head);
    else {
        map.addMove(id_head, X0, Y0);
        map.addMove(id_head, X1, Y1);
        heads.push_back({id_head, X1, Y1});
    }
}

void Snake::takeDecision() {

}