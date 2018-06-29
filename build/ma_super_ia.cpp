//
// Created by nils on 27/06/18.
//

#ifndef TEST_CELL_H
#define TEST_CELL_H

class Cell {
public:
    Cell();
    Cell(const Cell &);
    ~Cell();

    int id;
    bool used = false;
};

#endif //TEST_CELL_H
//
// Created by nils on 27/06/18.
//


Cell::Cell() = default;

Cell::~Cell() = default;

Cell::Cell(const Cell &) = default;
//
// Created by nils on 27/06/18.
//

#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <vector>
#include <iostream>
#include <ostream>

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
//
// Created by nils on 27/06/18.
//


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

void    Map::copy(const Map &copy) {
    for (int y = 0; y < MAPY; y++) {
        for (int x = 0; x < MAPX; x++) {
            map[y][x].id = copy.map[y][x].id;
            map[y][x].used = copy.map[y][x].used;
        }
    }
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

    std::cerr << size << std::endl;
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

    Map t;
    Map lotm;
    Map foty;
    Map cotb;
    Map tozer;
    Map taza;

    for (auto dir : directions) {
        std::cerr << "loop" << std::endl;
        std::cerr << dir.first << std::endl;

        Map toto;
        Map totm;
        Map toty;
        Map totb;
        Map totv;
        Map tota;

        /*
        int x = heads[id].x + dir.second.first;
        int y = heads[id].y + dir.second.second;

        std::vector<Head> h = headSort(heads, id, x, y);

         */

        /*
        test.addMove(id, x, y);


        test.propagation(h);

        if (test.getScore(id) > maxScore) {
            maxScore = test.getScore(id);
            bestDir = dir.first;
        }
        */
    }
    std::cout << bestDir << std::endl;
    heads.clear();
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    int N; // total number of players (2 to 4).
    int P; // your player number (0 to 3).
    std::cin >> N >> P; std::cin.ignore();
    Snake   snake(N, P);

    Map tata;
    Map tatn;
    Map tati;
    Map tatu;
    Map taty;
    Map tatt;

    std::cerr << "go" << std::endl;

    while (true) {
        for (int i = 0; i < N; i++) {
            int X0, Y0, X1, Y1;
            std::cin >> X0 >> Y0 >> X1 >> Y1; std::cin.ignore();
            snake.addHead(X0, Y0, X1, Y1, i);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl"
        snake.takeDecision();
        {
            int n, p;
            std::cin >> n >> p; std::cin.ignore();
        }
    }
}