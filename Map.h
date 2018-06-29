//
// Created by nils on 27/06/18.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <vector>
#include "Cell.h"

#define MAPY 20
#define MAPX 30

class Head {
public:
    int id;
    int x;
    int y;
};

class Map {
public:
    Map();
    Map(Map const &) = default;
    ~Map() = default;

    void    createMap();
    void    removeDeadPlayers(int);
    void    addMove(int, int, int);

    void    propagation(std::vector<Head>);
    int     getScore(int);

    std::vector<std::vector<Cell>>  map;
    int scores[4] = {0, 0, 0, 0};
};

#endif //TEST_MAP_H
