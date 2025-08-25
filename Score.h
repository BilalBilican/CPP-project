/*
 * Score.h
 *
 *  Created on: Nov 16, 2024
 *      Author: bilal
 */

#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int STARTING_BOMBS = 100; //each player starts with 100 bombs


// score class to keep track of the moves, bombs and destroyed ships
class Score {
public:
    int moves; // number of moves taken
    int bombs; // bombs remaining
    vector<string> destroyedShips;

    // constructor initializes moves and bombs
    Score() : moves(0), bombs(STARTING_BOMBS) {}

    // increase the number of moves and reduce bombs
    void incrementMoves() {
        moves++;
        bombs--;  // Decrease bombs with each move
    }

    // add a destroyed ship to the destroyed list
    void addDestroyedShip(const string& shipName) {
        destroyedShips.push_back(shipName);
    }

    // display the player's score on the screen after every move
    void displayScore(const string& playerName) {
        cout << "\n" << playerName << "'s Score:" << endl;
        cout << "Moves: " << moves << endl;
        cout << "Bombs left: " << bombs << endl;
        cout << "Ships Destroyed: ";
        if (destroyedShips.empty()) {
            cout << "None";
        } else {
            for (const auto& ship : destroyedShips) {
                cout << ship << " ";
            }
        }
        cout << endl;
    }
};



#endif // SCORE_H

