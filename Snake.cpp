//
// Created by nils on 27/06/18.
//

#include "Snake.h"

Snake::Snake(int p_nb, int id) : nb_players(p_nb), id(id) {
}

void    Snake::addHead(int X0, int Y0, int X1, int Y1, int id_head) {
    if (X0 == -1)
        map.removeDeadPlayers(id_head);
    else {
        map.addMove(id_head, X0, Y0);
        map.addMove(id_head, X1, Y1);
        heads.push_back({id_head, X1, Y1});
    }
}

std::vector<Head> Snake::headSort(std::vector<Head> const &oldheads, int idFirst, int x, int y) {
    unsigned long   size = oldheads.size();
    std::vector<Head>   newheads(size);

    newheads.push_back({oldheads[idFirst].id, x, y});
    for (int i = 1; i < size; i++) {
        // on met les têtes dans l'ordre de celle qui joue la première jusqu"à la dernière
        newheads.push_back(oldheads[(i + idFirst) % size]);
    }
    return newheads;
}

void    Snake::takeDecision() {

    // { direction, {x, y}}
    std::pair<std::string, std::pair<int, int>> directions[4] = {
            {"UP",    {0,  -1}},
            {"LEFT",  {-1, 0}},
            {"DOWN",  {0,  1}},
            {"RIGHT", {1,  0}}
    };

    int maxScore = 0;
    std::string bestDir = "UP";

    for (auto dir : directions) {
        Map test(map);

        int x = heads[id].x + dir.second.first;
        int y = heads[id].y + dir.second.second;

        std::vector<Head>   h = headSort(heads, id, x, y);
        test.addMove(id, x, y);

        test.propagation(h);

        if (test.getScore(id) > maxScore) {
            maxScore = test.getScore(id);
            bestDir = dir.first;
        }
    }
    std::cout << bestDir << std::endl;
}
