#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Snake.h"

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