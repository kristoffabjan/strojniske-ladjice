#ifndef GAME_H
#define GAME_H

#include "players/Player.h"
#include "Board.h"

class Game {
public:
    Game(Player* player1, Player* player2);
    void startMatch(int reps = 1); // Start the game loop
    Player* getWinner() const; // Check who is the winner
    void printBoards() const;
    char getSymbolForCell(int cellValue) const;
    int getScorePlayer1() const;
    int getScorePlayer2() const;
    int getMovesPlayer1() const;
    int getMovesPlayer2() const;

private:
    Player* player1_;
    Player* player2_;
    Board board1_; // board for player 1
    Board board2_; // board for player 2
    Player* currentPlayer_; // pointer to player whose turn it is
    int scorePlayer1_;
    int scorePlayer2_;
    int movesPlayer1_;
    int movesPlayer2_;
};

#endif //GAME_H
