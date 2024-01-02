#ifndef S23232067_H
#define S23232067_H

#include "Player.h"
#include <random>
#include <utility>
#include <vector>
#include <iostream> 

namespace s23232067
{

    class PlayerStudent : public Player
    {
    public:
        PlayerStudent();

        std::pair<int, int> getMove() override;
        Board setupBoard() override;
        //void logMoveResult(int x, int y, bool result) override;
        void logMoveResult(int x, int y);
        void logOpponentMove(int x, int y) override;
        //bool s23232067::PlayerStudent::notTouch(int x, int y, int size, Orientation orientation, Board board);
        bool notTouch(int x, int y, int size, Orientation orientation, Board board);

    private:
        std::mt19937 gen_;
        std::uniform_int_distribution<int> dist_;
        Board board_;

        // std::set<std::pair<int, int>> old_moves; //Set of old moves to be hit
        // std::set<std::pair<int, int>> old_miss; //Set of old misses
        // std::set<std::pair<int, int>> targetedCells; //Save targeted cells
        // std::set<std::pair<int, int>> hitCells; //Hit cells
        // std::set<std::pair<int, int>> miss; //Miss cells
        // std::set<std::pair<int, int>> toBeHit; //To be hit queue
        // std::pair<int, int> lastToBeHit; //Last TO BE HIT
        // std::set<std::pair<int, int>> doNotGuess; //Do not guess
    };

}

#endif // S23232067_H
