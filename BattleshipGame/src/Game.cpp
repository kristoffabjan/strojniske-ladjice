#include <iostream>
#include <iomanip>

#include "Game.h"

Game::Game(Player *player1, Player *player2)
    : player1_(player1),
      player2_(player2),
      currentPlayer_(player1),
      scorePlayer1_(0),
      scorePlayer2_(0),
      movesPlayer1_(0),
      movesPlayer2_(0) {}


// Start a match between the two players.
// reps: number of games to play
void Game::startMatch(int reps)
{

    Board *currentBoard = nullptr;
    Player *opponent = nullptr;

    for (int i = 0; i < reps; i++)
    {
        std::cout << "\n----------------------------------------\nStarting new game...\n";
        // Set up the game.
        // Place ships on the boards:
     
        board1_ = player1_->setupBoard();
        board2_ = player2_->setupBoard();

        // Check if the boards are valid
        bool board1valid = board1_.isSetupValid();
        bool board2valid = board2_.isSetupValid();
        if(!board1valid) {
            std::cout << "Board 1 is invalid!\n";
            if(!board2valid){
                std::cout << "Board 2 is invalid!\n";
            }else{
                scorePlayer2_++;
            }
            break;
        }
        if(!board2valid) {
            std::cout << "Board 2 is invalid!\n";
            if(board1valid){
                scorePlayer1_++;
            }
            break;
        }
        std::cout << "Boards set up successfully!\n";
        std::cout << "Printing boards!\n";

        printBoards();

        // player1_->printBoard();
        // player2_->printBoard();

        // Switch the current player and board.
        if (i % 2 == 0)
        {
            currentPlayer_ = player1_;
            opponent = player2_;
            currentBoard = &board2_;
        }
        else
        {
            currentPlayer_ = player2_;
            opponent = player1_;
            currentBoard = &board1_;
        }

        // Game loop:
        int moveCounterPlayer1 = 0; // Initialize move counter for Player1
        int moveCounterPlayer2 = 0; // Initialize move counter for Player2
        int tries = 0;
        while (true)
        {
            if (currentPlayer_ == player1_)
            {
                moveCounterPlayer1++;
                if (moveCounterPlayer1 > 200)
                {
                    std::cout << "Game stopped: Player1 move limit exceeded." << std::endl;
                    currentPlayer_ = nullptr;
                    break;
                }
            }
            else // currentPlayer_ == player2_
            {
                moveCounterPlayer2++;
                if (moveCounterPlayer2 > 200)
                {
                    std::cout << "Game stopped: Player2 move limit exceeded." << std::endl;
                    currentPlayer_ = nullptr;
                    break;
                }
            }

            // Print the current state of the game.
            // printBoards();

            // Get the next move from the current player.
            std::pair<int, int> pos = currentPlayer_->getMove(); // Player chooses a position to hit

            // Apply the move to the current board.
            bool moveResult = currentBoard->applyMove(pos.first, pos.second);
            // opponent is owner of currentBoard
            opponent->logOpponentMove(pos.first, pos.second); // Player gets to know where the opponent hit

            // Log the result of the move.
            // Before check for game over.
            currentPlayer_->logMoveResult(pos.first, pos.second, moveResult); // Player gets to know if they hit or missed

            // Check if the game is over.
            if (currentBoard->allShipsSunk())
            {
                // The current player wins.
                if (currentPlayer_ == player1_)
                {
                    scorePlayer1_++;
                }
                else
                { // currentPlayer_ == player2_
                    scorePlayer2_++;
                }
                movesPlayer1_ += moveCounterPlayer1;
                movesPlayer2_ += moveCounterPlayer2;
                break;
            }

            // Check if the move was a miss.
            if (!moveResult || tries > 20)
            {
                // The move was a miss.
                // Switch to the other player and update currentBoard accordingly.
                if (currentPlayer_ == player1_)
                {
                    currentPlayer_ = player2_;
                    currentBoard = &board1_;
                    opponent = player1_; // Switch opponent
                }
                else
                { // currentPlayer_ == player2_
                    currentPlayer_ = player1_;
                    currentBoard = &board2_;
                    opponent = player2_; // Switch opponent
                }
                tries = 0;
                continue;
            }
            else
            {
                tries++;
            }
        }

        // Print the final state of the game.
        printBoards();
        if (currentPlayer_ == nullptr)
        {
            std::cout << "The game ended in a draw!\n";
        }
        else
        { // (currentPlayer_ == player1_ || currentPlayer_ == player2_
            std::cout << "The winner of the game is " << currentPlayer_->getName() << "!\n";
        }
        std::cout << "Score: " << scorePlayer1_ << " - " << scorePlayer2_ << std::endl;
        std::cout << "Moves: " << moveCounterPlayer1 << " - " << moveCounterPlayer2 << std::endl;
        std::cout << "Moves total: " << movesPlayer1_ << " - " << movesPlayer2_ << std::endl;
        std::cout << "----------------------------------------\n";
    }
}

Player *Game::getWinner() const
{
    if (scorePlayer1_ > scorePlayer2_)
    {
        return player1_;
    }
    else if (scorePlayer1_ < scorePlayer2_)
    {
        return player2_;
    }
    else
    {
        return nullptr;
    }
}

void Game::printBoards() const
{
    std::cout << std::setw(22) << std::left << player1_->getName() << " vs. " << std::setw(22) << player2_->getName() << "\n";
    std::cout << "   ";
    for (int j = 0; j < board1_.getSize(); ++j)
    {
        std::cout << std::setw(2) << j + 1;
    }
    std::cout << "       ";
    for (int j = 0; j < board2_.getSize(); ++j)
    {
        std::cout << std::setw(2) << j + 1;
    }
    std::cout << "\n\n";

    for (int i = 0; i < board1_.getSize(); ++i)
    {
        std::cout << std::setw(2) << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < board1_.getSize(); ++j)
        {
            std::cout << std::setw(2) << getSymbolForCell(board1_.getCell(i, j));
        }

        std::cout << "    ";

        std::cout << std::setw(2) << static_cast<char>('A' + i) << " ";
        for (int j = 0; j < board2_.getSize(); ++j)
        {
            std::cout << std::setw(2) << getSymbolForCell(board2_.getCell(i, j));
        }
        std::cout << "\n";
    }
}

char Game::getSymbolForCell(int cellValue) const
{
    if (cellValue == 0)
    { // Unhit point
        return '+';
    }
    else if (cellValue == -1)
    { // Hit point that is water
        return '0';
    }
    else if (cellValue < -1)
    { // Hit point that is ship
        return 'X';
    }
    else
    { // Unhit ship point
        return 'S';
    }
}

int Game::getScorePlayer1() const
{
    return scorePlayer1_;
}

int Game::getScorePlayer2() const
{
    return scorePlayer2_;
}

int Game::getMovesPlayer1() const
{
    return movesPlayer1_;
}

int Game::getMovesPlayer2() const
{
    return movesPlayer2_;
}
