#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Snake.h"

using namespace std;

int main()
{
    int N; // total number of players (2 to 4).
    int P; // your player number (0 to 3).
    cin >> N >> P; cin.ignore();
    Snake   snake(N, P);

    while (true) {
        for (int i = 0; i < N; i++) {
            int X0, Y0, X1, Y1;
            cin >> X0 >> Y0 >> X1 >> Y1; cin.ignore();
            snake.addHead(X0, Y0, X1, Y1, i);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl"
        snake.takeDecision();
        {
            int n, p;
            cin >> n >> p; cin.ignore();
        }
    }
}