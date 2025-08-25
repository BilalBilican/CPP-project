/*
 * Board.h
 *
 *  Created on: Nov 12, 2024
 *      Author: bilal
 */


#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include "Ship.h"
using namespace std;

const int GRID_SIZE = 10; // the size of the game board, 10x10 grid

const string RED = "\033[31m"; //color for hit
const string BLUE = "\033[34m";  //color for miss
const string GREEN = "\033[32m";  // color of the ships
const string RESET = "\033[0m";

// board class to manage the game board
class Board {
private:
    char grid[GRID_SIZE][GRID_SIZE]; // grid to represent the board
    vector<Ship> ships; //list of ships placed on the board

public:
// constructor sets all cells to '.'
    Board() {
        for (int i = 0; i < GRID_SIZE; ++i)
            for (int j = 0; j < GRID_SIZE; ++j)
                grid[i][j] = '.';
    }

// function to display the board
    void displayBoard(const string& boardName, bool showShips = false) {
        cout << "\n" << boardName << ":\n";
        cout << "  ";
// print column numbers, 1 to 10
        for (int i = 1; i <= GRID_SIZE; ++i) cout << i << " ";
        cout << endl;

// print each row with letters, A to J
        for (int i = 0; i < GRID_SIZE; ++i) {
            cout << char('A' + i) << " ";
            for (int j = 0; j < GRID_SIZE; ++j) {

// use of colors to highlight hits, misses and ships
                if (grid[i][j] == 'X')
                    cout << RED << grid[i][j] << RESET << " ";
                else if (grid[i][j] == 'O')
                    cout << BLUE << grid[i][j] << RESET << " ";
                else if (grid[i][j] == 'S' && showShips)
                    cout << GREEN << grid[i][j] << RESET << " ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }

// function to place a ship on the board
    bool placeShip(Ship &ship, int x, int y, char orientation) {

// check if the ship can be placed without overlapping
        for (int i = 0; i < ship.size; ++i) {
            int nx = (orientation == 'H') ? x : x + i;
            int ny = (orientation == 'V') ? y : y + i;
            if (nx >= GRID_SIZE || ny >= GRID_SIZE || grid[nx][ny] != '.')
                return false; // ship can't be placed here
        }

// place the ship on the board
        for (int i = 0; i < ship.size; ++i) {
            int nx = (orientation == 'H') ? x : x + i;
            int ny = (orientation == 'V') ? y : y + i;
            grid[nx][ny] = 'S'; // Mark the cells with 'S'
            ship.coordinates.push_back({nx, ny}); // save coordinates of the ship
        }
        ships.push_back(ship); // Add ship to the list
        return true;
    }

// randomly places all ships for a player
    void placeShipsRandomly() {
        vector<Ship> shipList = {
            {"Carrier", 5}, {"Battleship", 4}, {"Cruiser", 3}, {"Submarine", 3}, {"Destroyer", 2}
        };
        for (auto &ship : shipList) {
            placeRandomShip(ship); // try to place each ship
        }
    }

// randomly finds a position for a single ship
    void placeRandomShip(Ship &ship) {
        bool placed = false;
        while (!placed) {
            int x = rand() % GRID_SIZE; // random row
            int y = rand() % GRID_SIZE; // random column
            char orientation = (rand() % 2 == 0) ? 'H' : 'V'; // horizontal or vertical
            placed = placeShip(ship, x, y, orientation); // placing the ship
        }
    }

// handles an attack on a specific cell
    char attack(int x, int y) {
        if (grid[x][y] == 'S') { // if there's a ship
            grid[x][y] = 'X'; // mark it as hit
            return 'H'; // return 'Hit'
        } else if (grid[x][y] == '.') { // if it's an empty cell
            grid[x][y] = 'O'; // mark it as a miss
            return 'O'; // return 'Mis'
        }
        return 'A'; // return 'Already attacked' if cell was previously hit
    }

// checks if a ship has been completely destroyed
    string checkDestroyedShip() {
        for (auto &ship : ships) {
            bool sunk = true;

// check if all parts of the ship have been hit
            for (auto coord : ship.coordinates) {
                if (grid[coord.first][coord.second] != 'X') {
                    sunk = false; // ship is not completely sunk
                    break;
                }
            }

// if ship is sunk and wasn't marked before, return its name
            if (sunk && !ship.isSunk) {
                ship.isSunk = true;
                return ship.name;
            }
        }
        return ""; // no ship was destroyed
    }

// checks if all ships have been sunk
    bool allShipsSunk() {
        for (const auto &ship : ships) {
            if (!ship.isSunk) return false; // if any ship isn't sunk, game continues
        }
        return true; // all ships are destroyed
    }
};



#endif // BOARD_H




