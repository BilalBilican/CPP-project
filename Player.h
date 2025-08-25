/*
 * Player.h
 *
 *  Created on: Nov 15, 2024
 *      Author: bilal
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Score.h"
#include "Board.h"
using namespace std;

// Player class
class Player {
public:
    Board board;
    Score score;
    string name;

    // constructor to set player's name
    Player(string n) : name(n) {}

    // function to place ships on the board
    void placeShips() {
        board.placeShipsRandomly();
    }

    // function to handle a player's turn
    bool takeTurn(Player &opponent) {
        string input;
        int x, y;
        char result;

        while (true) {
            cout << name << "'s turn. Enter coordinates (e.g., A5): ";
            cin >> input;

            // validate the player's input
            if (input.length() < 2 || input.length() > 3 || !isalpha(input[0]) || !isdigit(input[1])) {
                cout << "Invalid input. Enter coordinates in the format A1 to J10.\n";
                continue; //keep asking till good entered coordinates
            }

            // convert input to grid coordinates
            x = toupper(input[0]) - 'A';
            y = stoi(input.substr(1)) - 1;

            // check if coordinates are within the board
            if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
                cout << "Invalid coordinates. Please choose a position within A1 to J10.\n";
                continue;
            }

            // attack opponent's board
            result = opponent.board.attack(x, y);
            score.incrementMoves();

            // handling result of the attack
            if (result == 'H') {
                cout << "Hit!" << endl;

                string destroyedShip = opponent.board.checkDestroyedShip();
                if (!destroyedShip.empty()) {
                    score.addDestroyedShip(destroyedShip);
                    cout << name << " destroyed " << destroyedShip << "!" << endl;

             // check if all ships are destroyed
                    if (opponent.board.allShipsSunk()) {
                    return true; // game ends immediately
                    }
                }
            } else if (result == 'O') {
                cout << "Miss!" << endl;
                score.displayScore(name);
                return false; // end the turn
            } else {
                cout << "Already attacked this position!" << endl;
                continue; // retry if the position was already attacked
            }

            // show updated score after every move
            score.displayScore(name);
        }
    }
};

// AIPlayer class inherits from Player
class AIPlayer : public Player {
private:
    vector<vector<bool>> attacked;
    vector<pair<int, int>> targets;

public:
    AIPlayer(string n) : Player(n), attacked(GRID_SIZE, vector<bool>(GRID_SIZE, false)) {}

    bool takeTurn(Player &opponent) {
        int x, y;
        char result;

        // check if we have targets to prioritize
        while (true) {
            if (!targets.empty()) {
                auto target = targets.back();
                targets.pop_back();
                x = target.first;
                y = target.second;
            } else {
            	//// randomly select coordinates if no targets
                do {
                    x = rand() % GRID_SIZE;
                    y = rand() % GRID_SIZE;
                } while (attacked[x][y]);
            }

            attacked[x][y] = true;
            result = opponent.board.attack(x, y);
            score.incrementMoves();

            cout << name << " attacked " << char('A' + x) << (y + 1) << endl;

            if (result == 'H') {
                cout << "Hit!" << endl;

                addAdjacentTargets(x, y);
                string destroyedShip = opponent.board.checkDestroyedShip();
                if (!destroyedShip.empty()) {
                    score.addDestroyedShip(destroyedShip);
                    cout << name << " destroyed " << destroyedShip << "!" << endl;
            // check if all ships are destroyed
                    if (opponent.board.allShipsSunk()) {
                    return true; // game ends immediately
                    }
                }
            } else if (result == 'O') {
                cout << "Miss!" << endl;
                score.displayScore(name);
                return false; // end the turn
            }

            // display Agent smith's score after every move
            score.displayScore(name);
        }
    }

    // add adjacent cells to targets list if not already attacked
    void addAdjacentTargets(int x, int y) {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int i = 0; i < 4; ++i) {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && !attacked[nx][ny]) {
                targets.push_back(make_pair(nx, ny));
            }
        }
    }
};

#endif // PLAYER_H



