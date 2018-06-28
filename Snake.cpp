//
// Created by nils on 27/06/18.
//

#include "Snake.h"

Snake::Snake(int p_nb, int id) : nb_players(p_nb), id(id) {
    createMap();
}

void Snake::addHead(int X0, int Y0, int X1, int Y1, int id_head) {
    if (X0 == -1)
        remove_dead_player(map, i + 1);
    else {
        add_move(i+1, X0, Y0, map);
        add_move(i+1, X1, Y1, map);
        if (i != P - 1)
            heads = push_head(heads, X1, Y1, i + 1);
        else {
            MX1 = X1;
            MY1 = Y1;
        }
    }
}

void Snake::takeDecision() {

}