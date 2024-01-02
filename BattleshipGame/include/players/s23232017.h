#ifndef S23232017_H
#define S23230217_H

#include "Player.h"
#include <random>
#include <utility>
#include <set>


namespace s23232017
{

    class PlayerStudent : public Player
    {
    public:
        PlayerStudent();

        std::pair<int, int> getMove() override;
        Board setupBoard() override;
        void logMoveResult(int x, int y, bool result) override;
        void logOpponentMove(int x, int y) override;
        bool notTouching(int x, int y, int shipLength, Orientation orientation, Board board_);
        

    private:
        std::mt19937 gen_;
        std::uniform_int_distribution<int> dist_;

        std::set<std::pair<int, int>> old_moves; //Set of old moves to be hit
        std::set<std::pair<int, int>> old_miss; //Set of old misses
        std::set<std::pair<int, int>> targetedCells; //Save targeted cells
        std::set<std::pair<int, int>> hitCells; //Hit cells
        std::set<std::pair<int, int>> miss; //Miss cells
        std::set<std::pair<int, int>> toBeHit; //To be hit queue
        std::pair<int, int> lastToBeHit; //Last TO BE HIT
        std::set<std::pair<int, int>> doNotGuess; //Do not guess

        std::vector<int> shipSizes = {5, 4, 3, 3, 2};
    };

}

#endif // S232xxxxx_H
