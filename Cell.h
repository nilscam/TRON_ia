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
