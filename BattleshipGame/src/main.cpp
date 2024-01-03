#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <fstream>

#include "Game.h"
#include "players/Player.h"
#include "players/RandomPlayer.h"
#include "players/Player2.h"
#include "players/s23232067.h"
#include "players/s23232017.h"
#include "players/PlayerHuman.h"

int main()
{

    const int numPlayers = 2;

    // Create a list of players
    std::vector<Player *> players;
    //players.push_back(new RandomPlayer());
    //players.push_back(new Player2("Pl2"));
    players.push_back(new s23232067::PlayerStudent());
    players.push_back(new s23232017::PlayerStudent());
    // Adding more players here ...

    // Create a matrix to store the scores and moves
    std::array<std::array<int, numPlayers>, numPlayers> scores_table = {0};
    std::array<std::array<float, numPlayers>, numPlayers> moves_table = {0};

    // Run tournaments
    for (size_t i = 0; i < players.size(); ++i)
    {
        for (size_t j = i + 1; j < players.size(); ++j)
        {
            // Create the game with two different players
            Game game(players[i], players[j]);

            // Start the match for a fixed number of repetitions/games (default: 1)
            game.startMatch(2);

            // Display the winner of this pair
            if (game.getWinner() != nullptr)
            {
                std::cout << game.getWinner()->getName() << " won the match against "
                          << (game.getWinner() == players[i] ? players[j]->getName() : players[i]->getName()) << "!" << std::endl;
            }
            else
            {
                std::cout << "The match between " << players[i]->getName() << " and " << players[j]->getName() << " ended in a draw!" << std::endl;
            }

            // Update scores_table
            scores_table[i][j] = game.getScorePlayer1();
            scores_table[j][i] = game.getScorePlayer2();
            // Update moves_table
            if (game.getMovesPlayer1() != 0 && game.getScorePlayer1() != 0)
            {
                moves_table[i][j] += (float)game.getMovesPlayer1() / game.getScorePlayer1();
            }
            else
            {
                moves_table[i][j] += 99;
            }
            if (game.getMovesPlayer2() != 0 && game.getScorePlayer2() != 0)
            {
                moves_table[j][i] += (float)game.getMovesPlayer2() / game.getScorePlayer2();
            }
            else
            {
                moves_table[j][i] += 99;
            }
        }
    }

    // Open a file stream
    std::ofstream file("results.txt");

    // Print the tables
    int wins, points;
    double moves;

    // Print the results
    std::cout << "\nREZULTATI\n";
    std::cout << "----------\n";
    std::cout << std::setw(6) << " ";

    file << "\nREZULTATI\n";
    file << "----------\n";
    file << std::setw(6) << " ";

    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << std::right << std::setw(6) << players[i]->getName();
        file << std::right << std::setw(6) << players[i]->getName();
    }

    std::cout << std::right << std::setw(6) << "ZMAG"
              << std::right << std::setw(6) << "TOCK"
              << std::right << std::setw(6) << "POTEZ"
              << "\n";
    file << std::right << std::setw(6) << "ZMAG"
         << std::right << std::setw(6) << "TOCK"
         << std::right << std::setw(6) << "POTEZ"
         << "\n";

    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << std::setw(6) << players[i]->getName();
        wins = 0;
        points = 0;
        moves = 0;
        for (int j = 0; j < numPlayers; j++)
        {
            std::cout << std::right << std::setw(6) << scores_table[i][j];
            file << std::right << std::setw(6) << scores_table[i][j];
            points += scores_table[i][j];
            wins += (scores_table[i][j] > scores_table[j][i]);
            moves += moves_table[i][j] * scores_table[i][j];
        }
        if (points == 0)
        {
            points = 1;
        }
        std::cout << std::right << std::setw(6) << wins
                  << std::right << std::setw(6) << points
                  << std::right << std::setw(6) << moves / points << "\n";
        file << std::right << std::setw(6) << wins
             << std::right << std::setw(6) << points
             << std::right << std::setw(6) << moves / points << "\n";
    }

    // print moves
    std::cout << "\nPOTEZE\n";
    std::cout << "----------\n";
    std::cout << std::setw(6) << " ";
    file << "\nPOTEZE\n";
    file << "----------\n";
    file << std::setw(6) << " ";
    

    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << std::right << std::setw(6) << players[i]->getName();
        file << std::right << std::setw(6) << players[i]->getName();
    }

    std::cout << "\n";
    file << "\n";

    for (int i = 0; i < numPlayers; i++)
    {
        std::cout << std::right << std::setw(6) << players[i]->getName();
        file << std::right << std::setw(6) << players[i]->getName();
        for (int j = 0; j < numPlayers; j++)
        {
            std::cout << std::right << std::setw(6) << moves_table[i][j];
            file << std::right << std::setw(6) << moves_table[i][j];
        }
        std::cout << std::endl;
        file << "\n";
    }

    // Clean up dynamically allocated players
    for (Player *player : players)
    {
        delete player;
    }

    return 0;
}
