//
// Created by nils on 27/06/18.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <vector>
#include "Cell.h"

#define MAPY 20
#define MAPX 30

class Map {
public:
    Map();
    ~Map() = default;

    void    createMap();
    void    removeDeadPlayers(int);

    std::vector<std::vector<Cell>>  map;

};

#endif //TEST_MAP_H
