//
// Created by nils on 27/06/18.
//

#ifndef TEST_CELL_H
#define TEST_CELL_H

class Cell {
public:
    Cell();
    Cell(Cell const &) = default;
    ~Cell();

    int id;
    bool used = false;
};

#endif //TEST_CELL_H
//
// Created by nils on 27/06/18.
//


Cell::Cell() = default;

Cell::~Cell() = default;//
// Created by nils on 27/06/18.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <vector>

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
//
// Created by nils on 27/06/18.
//


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
            map[y][x].used = true;  \
            map[y][x].id = head.id; \
            nextHeads.push_back({head.id, x, y});   \
            scores[head.id] += 1;   \
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

int     Map::getScore(int id) {
    return scores[id];
}
//
// Created by nils on 27/06/18.
//

#ifndef TEST_AI_H
#define TEST_AI_H

#include <iostream>
#include <string>

class Snake {
public:

    Snake(int, int);
    ~Snake() = default;


    void    addHead(int, int, int, int, int);
    std::vector<Head>   headSort(std::vector<Head> const &, int, int, int);

    void    takeDecision();


private:

    Map map;
    int id;
    int nb_players;
    std::vector<Head>  heads;

};

#endif //TEST_AI_H
//
// Created by nils on 27/06/18.
//


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
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N; // total number of players (2 to 4).
    int P; // your player number (0 to 3).
    cin >> N >> P; cin.ignore();
    Snake   snake(N, P);

    while (true) {
        {
            int n, p;
            cin >> n >> p; cin.ignore();
        }
        for (int i = 0; i < N; i++) {
            int X0, Y0, X1, Y1;
            cin >> X0 >> Y0 >> X1 >> Y1; cin.ignore();
            snake.addHead(X0, Y0, X1, Y1, i);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl"
        snake.takeDecision();
    }
}