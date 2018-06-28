//
// Created by nils on 27/06/18.
//

#ifndef TEST_AI_H
#define TEST_AI_H

#include "Map.h"

class Snake {
public:

    Snake(int, int);
    ~Snake() = default;


    void    addHead(int, int, int, int, int);
    void    takeDecision();

private:

    Map map;
    int id;
    int nb_players;
};

#endif //TEST_AI_H
