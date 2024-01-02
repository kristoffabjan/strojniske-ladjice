#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <iostream>
#include <utility>
#include <random>
#include "../../include/players/Player2.h"

Player2::Player2(const std::string &name) : Player(name)
{
    gen_.seed(std::random_device()());
    dist_ = std::uniform_int_distribution<int>(0, 9);
}

std::pair<int, int> Player2::getMove()
{
    int first = dist_(gen_);
    int second = dist_(gen_);
    return std::make_pair(first, second);
}

Board Player2::setupBoard()
{
    board_.clearBoard();

    std::vector<int> shipSizes = {2, 3, 3, 4, 5};

    int x = 1;
    for (int shipSize : shipSizes)
    {
        if (!board_.placeShip(x, 3, shipSize, Orientation::Horizontal))
        {
            std::cout << "Failed to place ship of size " << shipSize << " at position (" << x << ", " << 0 << ")" << std::endl;
        }
        x += 2; // Increment by 2 to only use odd rows.
    }

    return board_;
}

void Player2::logMoveResult(int x, int y, bool result) {}
void Player2::logOpponentMove(int x, int y) {}
