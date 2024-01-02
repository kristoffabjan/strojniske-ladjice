#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <iostream>
#include <iomanip>
#include <utility>
#include <random>
#include "../../include/players/PlayerHuman.h"

PlayerHuman::PlayerHuman(const std::string &name) : Player(name){
    otherBoard_ = Board();
    for (int i = 0; i < otherBoard_.getSize(); i++) {
        for (int j = 0; j < otherBoard_.getSize(); j++) {
            otherBoard_.setCell(i, j, -1);
        }
    }
}

std::pair<int, int> PlayerHuman::getMove()
{
    char colon;
    int x, y;
    board_.printBoard();
    std::cout << "Enter your move (format: row, column): ";
    std::cin >> x >> colon >> y;
    return std::make_pair(x, y);
}

Board PlayerHuman::setupBoard()
{
    board_.clearBoard();

    std::vector<int> shipSizes = {5, 4, 3, 3, 2};

    std::cout << name_ << ", please place your ships." << std::endl;

    for (int shipSize : shipSizes)
    {
        int row, col, orientation;
        char colon;
        std::cout << "Enter the starting location of the ship size " << shipSize << " (format: row, column): ";
        std::cin >> row >> colon >> col;
        std::cout << "Enter ship orientation (0 for horizontal, 1 for vertical): ";
        std::cin >> orientation;
        if (!board_.placeShip(row, col, shipSize, intToOrientation(orientation)))
        {
            std::cout << "Failed to place ship of size " << shipSize << " at position (" << row << ", " << col << ")" << std::endl;
        }
        board_.printBoard();
    }

    return board_;
}

void PlayerHuman::logMoveResult(int x, int y, bool result) {
    if (result) {
        std::cout << "Hit!" << std::endl;
    } else {
        std::cout << "Miss!" << std::endl;
    }
    otherBoard_.setCell(x, y, result);
    printBoards();
}

void PlayerHuman::logOpponentMove(int x, int y) {}

void PlayerHuman::printBoards() const
{
    std::cout << std::setw(25) << std::left << " My board " << std::setw(22) << "Opponents board" << "\n";
    std::cout << "   ";
    for (int j = 0; j < board_.getSize(); ++j)
    {
        std::cout << std::setw(2) << j + 1;
    }
    std::cout << "       ";
    for (int j = 0; j < otherBoard_.getSize(); ++j)
    {
        std::cout << std::setw(2) << j + 1;
    }
    std::cout << "\n\n";

    for (int i = 0; i < board_.getSize(); ++i)
    {
        std::cout << std::setw(2) << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < board_.getSize(); ++j)
        {
            std::cout << std::setw(2) << board_.getCell(i, j);
        }

        std::cout << "    ";

        std::cout << std::setw(2) << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < otherBoard_.getSize(); ++j)
        {
            std::cout << std::setw(2) << std::right << otherBoard_.getCell(i, j);
        }
        std::cout << "\n";
    }
}
