#include <cassert>
#include "Board.h"

void testBoardSetupValidity() {
    // Test 1: Correct setup
    Board board1 = Board();
    assert(board1.placeShip(0, 0, 5, Orientation::Horizontal) == true);
    assert(board1.placeShip(2, 0, 4, Orientation::Horizontal) == true);
    assert(board1.placeShip(4, 0, 3, Orientation::Horizontal) == true);
    assert(board1.placeShip(6, 0, 3, Orientation::Horizontal) == true);
    assert(board1.placeShip(8, 0, 2, Orientation::Horizontal) == true);
    // board1.printBoard();
    assert(board1.isSetupValid() == true);

    // Test 2: Too many ships of length 5
    Board board2 = Board();
    assert(board2.placeShip(0, 0, 5, Orientation::Horizontal) == true);
    assert(board2.placeShip(2, 0, 5, Orientation::Horizontal) == true);
    assert(board2.placeShip(4, 0, 4, Orientation::Horizontal) == true);
    assert(board2.placeShip(6, 0, 3, Orientation::Horizontal) == true);
    assert(board2.placeShip(8, 0, 3, Orientation::Horizontal) == true);
    assert(board2.placeShip(5, 8, 2, Orientation::Horizontal) == true);
    // board2.printBoard();
    assert(board2.isSetupValid() == false);

    // Test 3: Missing ship of length 2
    Board board3 = Board();
    assert(board3.placeShip(0, 0, 5, Orientation::Horizontal) == true);
    assert(board3.placeShip(2, 0, 4, Orientation::Horizontal) == true);
    assert(board3.placeShip(4, 0, 3, Orientation::Horizontal) == true);
    assert(board3.placeShip(6, 0, 3, Orientation::Horizontal) == true);
    // board3.printBoard();
    assert(board3.isSetupValid() == false);

    // // Test 4: Ships too close
    // Board board4 = Board();
    // assert(board4.placeShip(0, 0, 5, Orientation::Horizontal) == true);
    // assert(board4.placeShip(0, 1, 4, Orientation::Horizontal) == true); // Too close to the first ship
    // // board4.printBoard();
    // assert(board4.isSetupValid() == false);

    // // Test 5: Touching ships of length 3 (horizontally)
    // Board board5 = Board();
    // assert(board5.placeShip(0, 0, 5, Orientation::Horizontal) == true);
    // assert(board5.placeShip(0, 2, 4, Orientation::Horizontal) == true);
    // assert(board5.placeShip(0, 4, 3, Orientation::Horizontal) == true);
    // assert(board5.placeShip(3, 4, 3, Orientation::Horizontal) == true);
    // assert(board5.placeShip(2, 8, 2, Orientation::Horizontal) == true);
    // // board5.printBoard();
    // assert(board5.isSetupValid() == false);

    // // Test 6: Touching ships of length 3 (diagonally)
    // Board board6 = Board();
    // assert(board6.placeShip(0, 0, 5, Orientation::Horizontal) == true);
    // assert(board6.placeShip(0, 2, 4, Orientation::Horizontal) == true);
    // assert(board6.placeShip(0, 4, 3, Orientation::Horizontal) == true);
    // assert(board6.placeShip(3, 5, 3, Orientation::Horizontal) == true);
    // assert(board6.placeShip(2, 8, 2, Orientation::Horizontal) == true);
    // // board6.printBoard();
    // assert(board6.isSetupValid() == false);
}

int main() {
    testBoardSetupValidity();
    return 0;
}
