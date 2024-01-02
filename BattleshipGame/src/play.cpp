#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <fstream>

#include "Game.h"
#include "players/Player.h"
#include "players/PlayerHuman.h"


int main() {

    Game game(new PlayerHuman("Pl1"), new PlayerHuman("Pl2"));

    game.startMatch();

    std::cout << "The winner is: " << game.getWinner()->getName() << std::endl;

    


    return 0;
}