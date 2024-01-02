#include <iostream>
// #include "players/Player2.h"
// #include "players/s232xxxxx.h"
#include "players/PlayerHuman.h"
#include "Board.h"

int main()
{
    // RandomPlayer player("Test Player");
    // Board board = player.setupBoard();

    // board.printBoard();
    // // print bool as text
    // std::cout << std::boolalpha << board.isSetupValid();

    // Board myboard = Board();
    // myboard.placeShip(5, 3, 5, Orientation::Horizontal);
    // myboard.placeShip(3, 5, 4, Orientation::Vertical);

    // myboard.printBoard();

    PlayerHuman player("Test Player");
    Board board = player.setupBoard();
    player.getMove();


    return 0;
}