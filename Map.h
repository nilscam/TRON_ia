//
// Created by nils on 27/06/18.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <vector>
#include <iostream>
#include <ostream>
#include "Cell.h"

#define MAPY 20
#define MAPX 30

class Head {
public:
    Head() = default;
    ~Head() = default;

    int id;
    int x;
    int y;
};

class Map {
public:
    Map();
    Map(const Map &);
    ~Map() = default;

    void    copy(const Map &);
    void    createMap();
    void    removeDeadPlayers(int);
    void    addMove(int, int, int);

    void    propagation(std::vector<Head> &);
    int     getScore(int);

    std::vector<std::vector<Cell>>  map;
    int scores[4] = {0, 0, 0, 0};
};

std::ostream& operator<<(std::ostream &, const Map &);


#endif //TEST_MAP_H
