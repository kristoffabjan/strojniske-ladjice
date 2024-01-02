#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Orientation.h"

class Board {
public:
    Board();
    bool placeShip(int x, int y, int length, Orientation orientation); // Place the ship at a certain position
    bool markHit(int x, int y); // Mark a hit on the board
    bool isValidPosition(int x, int y, int shipLength, Orientation orientation) const; // Check if a position is valid
    void printBoard() const; // Display the board
    bool allShipsSunk() const; // Check if all ships are sunk
    bool allShipsPlaced() const; // Check if all ships are placed
    bool applyMove(int x, int y); // Apply a move to the board
    int getCell(int x, int y) const; // Get the value of a cell
    bool setCell(int x, int y, int val); // Set the value of a cell
    int getSize() const; // Get the size of the board
    bool isSetupValid() const; // Check if the setup is valid
    void clearBoard(); // Clear the board

private:
    static const int size_ = 10;
    int board_[size_][size_];
};

#endif //BOARD_H
