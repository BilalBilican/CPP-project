/*
 * Game.h
 *
 *  Created on: Nov 12, 2024
 *      Author: bilal
 */
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"

using namespace std;

class Game {
private:
    Player human;
    AIPlayer ai;

public:
    // constructor to set up the players
    Game() : human("Human"), ai("A.Smith") {}

    // function to start the game
    void start() {
        char showAIShips;
        //ask the user if they want to see the AI's ships
        cout << "Would you like to reveal AI's ships? (y/n): ";
        cin >> showAIShips;

        //check if the user sais 'yes' (y)
        bool revealAI = (tolower(showAIShips) == 'y');

        human.placeShips();
        ai.placeShips();
        bool humanTurn = true;

        while (true) {
            human.board.displayBoard("Human's Board", true);
            ai.board.displayBoard("AI's Board", revealAI);

            if (humanTurn) {
                cout << human.name << "'s turn!" << endl;
                if (!human.takeTurn(ai)) {
                    humanTurn = false; // end turn on a miss
                }
                if (ai.board.allShipsSunk()) {
                    cout << "You win!" << endl;
                    break;
                }
            } else {
                cout << ai.name << "'s turn!" << endl;
                if (!ai.takeTurn(human)) {
                    humanTurn = true; // end turn on a miss
                }
                if (human.board.allShipsSunk()) {
                    cout << "A.Smith wins!" << endl;
                    break;
                }
            }
        }
        // display the final boards at the end of the game
        cout << "\n=== Final Boards ===" << endl;

        human.board.displayBoard("Final Human's Board", true);
        ai.board.displayBoard("Final AI's Board", true);
    }
};

#endif // GAME_H



