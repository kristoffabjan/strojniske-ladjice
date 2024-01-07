#ifndef KRISTOF_H
#define KRISTOF_H

#include "Player.h"
#include <random>
#include <utility>
#include <vector>
#include <iostream>
#include <set>

namespace Kristof
{

    class PlayerStudent : public Player
    {
    public:
        PlayerStudent();

        std::pair<int, int> getMove() override;
        Board setupBoard() override;
        // void logMoveResult(int x, int y, bool result) override;
        void logMoveResult(int x, int y);
        void logOpponentMove(int x, int y) override;
        // bool Kristof::PlayerStudent::notTouch(int x, int y, int size, Orientation orientation, Board board);
        bool notTouch(int x, int y, int size, Orientation orientation, Board board);
        // -zadnja koordinata na prejšnji potezi
        // std::pair<int, int> koordinata_zadnje_poteze;

        // -množica koordinat, ki smo jih ciljali
        std::set<std::pair<int, int>> nastreljane_pozicije;
        std::pair<int, int> lastMove;
        bool wasLastHit;
        std::vector<std::pair<int, int>> hitPositions;

        // bool zadnja_poteza_zadela = false;

    private:
        std::mt19937 gen_;
        std::uniform_int_distribution<int> dist_;
        Board board_;
    };

}

#endif // KRISTOF_H
