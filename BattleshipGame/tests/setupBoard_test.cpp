#include <cassert>
#include <iostream>
#include "players/RandomPlayer.h"
#include "Board.h"

int main()
{
    RandomPlayer player = RandomPlayer();
    Board board = player.setupBoard();
    assert(board.isSetupValid());

    std::cout << "Printing board..." << std::endl;
    board.printBoard();

    return 0;
}