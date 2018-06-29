//
// Created by nils on 27/06/18.
//

#ifndef TEST_AI_H
#define TEST_AI_H

#include <iostream>
#include <string>
#include "Map.h"

class Head {
public:
    int id;
    int x;
    int y;
};

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
