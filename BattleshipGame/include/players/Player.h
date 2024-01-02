#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <utility>
#include "../Board.h"

class Player {
public:
    Player(const std::string& name) : name_(name), board_(Board()) {}

    virtual std::pair<int, int> getMove() = 0; // Pure virtual function
    virtual Board setupBoard() = 0; // Pure virtual function
    std::string getName() const { return name_; }
    virtual void logMoveResult(int x, int y, bool result);
    virtual void logOpponentMove(int x, int y);
    void printBoard() const; // Print the board

protected:
    std::string name_;
    Board board_;
};

#endif //PLAYER_H
