#include <iostream>
#include "../../include/players/Player.h"

void Player::printBoard() const
{
    std ::cout << "Printing " << name_ << "'s board:" << std::endl;
    board_.printBoard();
}

void Player::logMoveResult(int x, int y, bool result) {}

void Player::logOpponentMove(int x, int y) {}