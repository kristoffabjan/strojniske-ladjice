#ifndef S232xxxxx_H
#define S232xxxxx_H

#include "Player.h"
#include <random>
#include <utility>

namespace s232xxxxx
{

    class PlayerStudent : public Player
    {
    public:
        PlayerStudent();

        std::pair<int, int> getMove() override;
        Board setupBoard() override;
        void logMoveResult(int x, int y, bool result) override;
        void logOpponentMove(int x, int y) override;

    private:
        std::mt19937 gen_;
        std::uniform_int_distribution<int> dist_;
    };

}

#endif // S232xxxxx_H
