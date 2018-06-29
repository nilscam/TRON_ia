//
// Created by nils on 27/06/18.
//

#include "Map.h"

Map::Map() {
    createMap();
}

Map::Map(const Map &copy) {
    map.reserve(20);
    for (int y = 0; y < MAPY; y++) {
        std::vector<Cell> row(30);
        for (int x = 0; x < MAPX; x++) {
            row[x] = Cell();
            row[x].id = copy.map[y][x].id;
            row[x].used = copy.map[y][x].used;
        }
        map[y] = row;
    }
}

std::ostream &operator<<(std::ostream &out, const Map &toDisplay) {
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 30; x++) {
            if (toDisplay.map[y][x].used) {
                out << toDisplay.map[y][x].id;
            } else {
                out << " ";
            }
        }
        out << std::endl;
    }
    return out;
}

void Map::createMap() {
    std::cerr << "map Create" << std::endl;
    map.reserve(20);
    for (int y = 0; y < 20; y++) {
        std::vector<Cell> row(30);
        for (int x = 0; x < 30; x++) {
            row[x] = Cell();
        }
        map[y] = row;
    }
    std::cerr << "Success" << std::endl;
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
            map[y][x].used = true;  \
            map[y][x].id = head.id; \
            nextHeads.push_back({head.id, x, y});   \
            scores[head.id] += 1;   \
        }})

void    Map::propagation(std::vector<Head> &heads) {
    bool    mapIsFilled = false;

    while (!mapIsFilled) {

        std::vector<Head>   nextHeads;

        for (auto head : heads) {
            TRY_PROP(head.x + 1, head.y); // RIGHT
            TRY_PROP(head.x - 1, head.y); // LEFT
            TRY_PROP(head.x, head.y - 1); // UP
            TRY_PROP(head.x, head.y + 1); // DOWN
        }

        if (nextHeads.empty())
            mapIsFilled = true;
        else {
            heads = nextHeads;
            nextHeads.shrink_to_fit();
        }
    }
}

int     Map::getScore(int id) {
    return scores[id];
}
