#ifndef PLAYER2_H
#define PLAYER2_H

#include "Player.h"
#include <random>
#include <utility>

class Player2 : public Player {
public:
    Player2(const std::string& name);

    std::pair<int, int> getMove() override;
    Board setupBoard() override;
    void logMoveResult(int x, int y, bool result) override;
    void logOpponentMove(int x, int y) override;

private:
    std::mt19937 gen_;
    std::uniform_int_distribution<int> dist_;
};

#endif //PLAYER2_H
