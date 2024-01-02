#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H

#include "Player.h"
#include <random>
#include <utility>

class PlayerHuman : public Player {
public:
    PlayerHuman(const std::string& name);

    std::pair<int, int> getMove() override;
    Board setupBoard() override;
    void logMoveResult(int x, int y, bool result) override;
    void logOpponentMove(int x, int y) override;
    void printBoards() const;

private:
    Board otherBoard_;

};

#endif //PLAYERHUMAN_H
