#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include "Player.h"
#include <random>
#include <utility>

class RandomPlayer : public Player {
public:
    RandomPlayer();

    std::pair<int, int> getMove() override;
    Board setupBoard() override;
    void logMoveResult(int x, int y, bool result) override;
    void logOpponentMove(int x, int y) override;

private:
    std::mt19937 gen_;
    std::uniform_int_distribution<int> dist_;
};

#endif //RANDOM_PLAYER_H
