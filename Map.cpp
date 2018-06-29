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
        for (int x = 0; x < MAPX; x++) {
            if (map[y][x].used && id == map[y][x].id) {
                map[y][x].used = false;
            }
        }
    }
}

void    Map::addMove(int id, int x, int y) {
    map[y][x].used = true;
    map[y][x].id = id;
}

#define TRY_PROP(x, y) ({ if ((x) >= 0 && (y) >= 0 && x < MAPX && y < MAPY && !map[y][x].used) {    \
            map[y][x].used = true; \
            map[y][x].id = head.id; \
            nextHeads.push_back({head.id, x, y});   \
        }})

void    Map::propagation(std::vector<Head> heads) {
    bool    mapIsFilled = false;

    while (!mapIsFilled) {

        std::vector<Head>   nextHeads;
        nextHeads.reserve(heads.size() * 4);

        for (auto head : heads) {
            TRY_PROP(head.x + 1, head.y); // RIGHT
            TRY_PROP(head.x - 1, head.y); // LEFT
            TRY_PROP(head.x, head.y - 1); // UP
            TRY_PROP(head.x, head.y + 1); // DOWN
        }
        if (nextHeads.empty())
            mapIsFilled = true;
    }
}

