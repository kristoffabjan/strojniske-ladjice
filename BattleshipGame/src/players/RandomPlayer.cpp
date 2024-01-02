#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <iostream>
#include <utility>
#include <random>
#include "../../include/players/RandomPlayer.h"

RandomPlayer::RandomPlayer() : Player("Rnd")
{
    gen_.seed(std::random_device()());
    dist_ = std::uniform_int_distribution<int>(0, 9);
}

std::pair<int, int> RandomPlayer::getMove()
{
    int first = dist_(gen_);
    int second = dist_(gen_);
    return std::make_pair(first, second);
}

Board RandomPlayer::setupBoard()
{
    board_.clearBoard();

    std::vector<int> shipSizes = {5, 4, 3, 3, 2};

    int x = 0;
    for (int shipSize : shipSizes)
    {
        if (!board_.placeShip(x, 0, shipSize, Orientation::Horizontal))
        {
            std::cout << "Failed to place ship of size " << shipSize << " at position (" << x << ", " << 0 << ")" << std::endl;
        }
        x += 2; // Increment by 2 to only use odd rows.
    }

    return board_;
}

void RandomPlayer::logMoveResult(int x, int y, bool result) {}
void RandomPlayer::logOpponentMove(int x, int y) {}
