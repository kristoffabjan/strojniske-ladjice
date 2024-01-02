#ifndef S23232067_H
#define S23232067_H

#include "Player.h"
#include <random>
#include <utility>
#include <vector>
#include <iostream> 
#include <set>

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
        // -zadnja koordinata na prejšnji potezi
        std::pair<int, int> koordinata_zadnje_poteze;

        // -množica koordinat, ki smo jih ciljali
        std::set<std::pair<int, int>> nastreljane_pozicije;

        bool zadnja_poteza_zadela = false;

    private:
        std::mt19937 gen_;
        std::uniform_int_distribution<int> dist_;
        Board board_;

    };

}

#endif // S23232067_H
