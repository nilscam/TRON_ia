//
// Created by nils on 27/06/18.
//

#include "Map.h"

Map::Map() {
    createMap();
}

void Map::createMap() {
    map.reserve(20);
    for (int y = 0; y < 20; y++) {
        std::vector<Cell> row(30);
        for (int x = 0; x < 30; x++) {
            row[x] = Cell();
        }
        map[y] = row;
    }
}

void    Map::removeDeadPlayers(int id) {
    for (int y = 0; y < MAPY; y++) {
        for (int x)
    }
}
