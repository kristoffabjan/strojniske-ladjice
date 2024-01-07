#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <iostream>
#include <utility>
#include <random>
#include <vector>
#include "../../include/players/Kristof.h"
// #include <xlocale>
#include <set>
#include <algorithm>
#include <variant>
#include <sstream>

/*Konstruktor za PlayerStudent, ki se izvede enkrat na začetku igre.
Zgenerirati želimo random števila, ki nam bodo predstavljala pozicije na katere bomo postavljali ladjice in streljali.
Polje je velikosti 10x10, zato je potrebno generirati števila med 0 in 9. To naredimo z std::uniform_int_distribution<int>(0, 9).*/
Kristof::PlayerStudent::PlayerStudent() : Player("Kristof")
{

    gen_.seed(std::random_device()());
    dist_ = std::uniform_int_distribution<int>(0, 9);
}

std::pair<int, int> generateRandomPositionKristof()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_(0, 9); // Assuming the range is 0-9

    int x = dist_(gen);
    int y = dist_(gen);
    std::pair<int, int> position = std::make_pair(x, y);

    return position;
}

bool isWithinBoardKristof(int x, int y)
{
    return x >= 0 && x <= 9 && y >= 0 && y <= 9;
}

// Funkcija, ki se izvede vsakič, ko je naša poteza. Vrniti moramo par števil x in y, ki predstavljata pozicijo na katero želimo streljati.
std::pair<int, int> Kristof::PlayerStudent::getMove()
{
    // 0: Water
    // -1: Missed shot
    // 1: Hit shot
    // >1: Ship
    if (!nastreljane_pozicije.empty()) // smo že streljali
    {
        // std::cout << "The set nastreljane_pozicije is not empty." << std::endl;
        std::pair<int, int> new_position;
        if (wasLastHit == true)
        {
            // std::cout << "In was last hit" << std::endl;
            // If the last move was a hit, generate a position in the vicinity of the last move.
            // This is a simple strategy that tries the cell to the right of the last hit.
            // You might want to improve this to try other directions and handle the board edges.
            int dx[] = {0, -1, 0, 1}; // Changes for the x coordinate for left, up, right, down
            int dy[] = {-1, 0, 1, 0}; // Changes for the y coordinate for left, up, right, down

            // Check neighbouring cells in the order left, up, right, down
            // Check if the cell is within the board and if it has already been hit
            int direction = 0; // Start with the left direction
            int counter = 0;
            while (!isWithinBoardKristof(lastMove.first + dx[direction], lastMove.second + dy[direction]) || nastreljane_pozicije.count({lastMove.first + dx[direction], lastMove.second + dy[direction]}) > 0)
            {
                direction = (direction + 1) % 4; // Move to the next direction

                if (counter >= 3)
                {
                    break;
                }
                counter++;
            }
            counter = 0;

            new_position = std::make_pair(lastMove.first + dx[direction], lastMove.second + dy[direction]);
        }
        else
        {
            // std::cout << "last was missed" << std::endl;
            // If the last move was not a hit, generate a random position.
            // Ta del bi lahko optimizirali, ker če zadnji lokacija ni bila zadeta, ne pomeni nujno,
            // da v bljižini ni nobene ladje.
            new_position = generateRandomPositionKristof();
        }

        nastreljane_pozicije.insert(new_position);
        lastMove = new_position;
        wasLastHit = board_.getCell(new_position.first, new_position.second) >= 2 && board_.getCell(new_position.first, new_position.second) <= 5;
        return new_position;
    }

    // nismo še streljali
    std::pair<int, int> random_position = generateRandomPositionKristof();
    std::cout << "The set nastreljane_pozicije is empty." << std::endl;
    nastreljane_pozicije.insert(random_position);
    wasLastHit = board_.getCell(random_position.first, random_position.second) >= 2 && board_.getCell(random_position.first, random_position.second) <= 5;
    lastMove = random_position;
    return random_position;
}

/*To funkcijo uporabimo za postavitev ladjic na polje. Vrniti moramo Board, ki predstavlja naše polje. Ladjice na polje postavljamo naključno, pri tem pa moramo
upoštevati, da imamo 5 ladjic velikosti 5, 4, 3, 3 in 2. Te se med sabo ne smejo dotikati, lahko pa jih postavljamo horizontalno ali navpično. Začnemo postavljati
na vedno drugi random poziciji x, y, random določimo tudi prvo ladjico in njeno orientacijo (navpično ali horizontalno).*/

Board Kristof::PlayerStudent::setupBoard()
{
    // Ustvarimo vektor ladjic dolžin 5, 4, 3, 3 in 2
    std::vector<int> ships = {5, 4, 3, 3, 2};

    // Izpraznimo polje velikosti 10x10
    board_.clearBoard();

    // Postavimo ladjice iz vektorja ship in pazimo, da zadostujejo funkciji notTouch() in isValidPosition()
    for (int ship : ships)
    {
        int x = dist_(gen_);
        int y = dist_(gen_);
        Orientation orientation = static_cast<Orientation>(dist_(gen_) % 2);

        int fail_count = 0;

        //
        while (!board_.isValidPosition(x, y, ship, orientation) || !notTouch(x, y, ship, orientation, board_))
        {
            x = dist_(gen_);
            y = dist_(gen_);
            orientation = static_cast<Orientation>(dist_(gen_) % 2);

            fail_count++;
            if (fail_count > 1000)
            {
                std::cout << "Ne moremo postaviti ladjice, poskusimo ponovno." << std::endl;
                board_.clearBoard();
                setupBoard();
            }
        }

        board_.placeShip(x, y, ship, orientation);
    }

    return board_;
}

// To je funkcija, ki se izvede po vsakem strelu in nam shranjuje podatke o tem ali smo zadeli ali zgrešili, ter nam le to sporoči s true ali false.
void Kristof::PlayerStudent::logMoveResult(int x, int y)
{
    if (board_.markHit(x, y) == true)
    {
        true;
    }
    else
    {
        false;
    }
}

void Kristof::PlayerStudent::logOpponentMove(int x, int y) {}

// Funkcija, ki preveri ali se ladje med sabo dotikajo. V primeru, da se dotikajo vrne false, v primeru, da se ne dotikajo vrne true.
bool Kristof::PlayerStudent::notTouch(int x, int y, int shipLength, Orientation orientation, Board board_)
{

    if (orientation == Orientation::Horizontal)
    {
        for (int dx = 0; dx < 3; dx++)
        {
            for (int dy = 0; dy < shipLength + 2; dy++)
            {
                int x_ = x - 1 + dx;
                int y_ = y - 1 + dy;
                // Preveri, da ne gremo izven polja
                if (x_ < 0 || x_ > 9 || y_ < 0 || y_ > 9)
                {
                    continue;
                }
                if (board_.getCell(x_, y_) != 0)
                {

                    return false;
                }
            }
        }
    }
    else
    {
        for (int dx = 0; dx < shipLength + 2; dx++)
        {
            for (int dy = 0; dy < 3; dy++)
            {
                int x_ = x - 1 + dx;
                int y_ = y - 1 + dy;
                // Ponovno preveri, da smo v polju
                if (x_ < 0 || x_ > 9 || y_ < 0 || y_ > 9)
                {
                    continue;
                }
                if (board_.getCell(x_, y_) != 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}
