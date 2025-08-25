/*
 * Ship.h
 *
 *  Created on: Nov 12, 2024
 *      Author: bilal
 */

#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// info about each ship
struct Ship {
    string name; //name of the ship
    int size; // how many cells the ship covers
    vector<pair<int, int>> coordinates; //the coordinates it covers
    bool isSunk; // whether a ship is sunk or not

    // constructor sets the ship's name, size and sunk status
    Ship(string n, int s) : name(n), size(s), isSunk(false) {}
};


#endif // SHIP_H

