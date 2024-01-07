#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <iostream>
#include <utility>
#include <random>
#include <vector>
#include "../../include/players/s23232067.h"
// #include <xlocale>
#include <set>
#include <algorithm>
#include <variant>
#include <sstream>

/*Konstruktor za PlayerStudent, ki se izvede enkrat na začetku igre.
Zgenerirati želimo random števila, ki nam bodo predstavljala pozicije na katere bomo postavljali ladjice in streljali.
Polje je velikosti 10x10, zato je potrebno generirati števila med 0 in 9. To naredimo z std::uniform_int_distribution<int>(0, 9).*/
s23232067::PlayerStudent::PlayerStudent() : Player("32067")
{

    gen_.seed(std::random_device()());
    dist_ = std::uniform_int_distribution<int>(0, 9);
}

std::pair<int, int> generateRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_(0, 9); // Assuming the range is 0-9

    int x = dist_(gen);
    int y = dist_(gen);
    std::pair<int, int> position = std::make_pair(x, y);

    return position;
}

bool isWithinBoard(int x, int y)
{
    return x >= 0 && x <= 9 && y >= 0 && y <= 9;
}

std::set<std::pair<int, int>> getAdjacentNonHitPositions(int x, int y, std::set<std::pair<int, int>> pozicije)
{
    std::set<std::pair<int, int>> adjacent_positions;

    // x - 1, y
    if (isWithinBoard(x - 1, y) && pozicije.find(std::make_pair(x - 1, y)) == pozicije.end())
    {
        adjacent_positions.insert(std::make_pair(x - 1, y));
    }

    // x + 1, y
    if (isWithinBoard(x + 1, y) && pozicije.find(std::make_pair(x + 1, y)) == pozicije.end())
    {
        adjacent_positions.insert(std::make_pair(x + 1, y));
    }

    // x, y - 1
    if (isWithinBoard(x, y - 1) && pozicije.find(std::make_pair(x, y - 1)) == pozicije.end())
    {
        adjacent_positions.insert(std::make_pair(x, y - 1));
    }

    // x, y + 1
    if (isWithinBoard(x, y + 1) && pozicije.find(std::make_pair(x, y + 1)) == pozicije.end())
    {
        adjacent_positions.insert(std::make_pair(x, y + 1));
    }

    return adjacent_positions;
}

// Funkcija, ki se izvede vsakič, ko je naša poteza. Vrniti moramo par števil x in y, ki predstavljata pozicijo na katero želimo streljati.
std::pair<int, int> s23232067::PlayerStudent::getMove()
{
    // 0: Water
    // -1: Missed shot
    // 1: Hit shot
    // >1: Ship
    if (!nastreljane_pozicije.empty()) // smo že streljali
    {
        std::pair<int, int> new_position;

        if (!targeted_positions.empty())
        {
            new_position = *targeted_positions.begin();
            targeted_positions.erase(targeted_positions.begin());
            wasLastHit = board_.getCell(new_position.first, new_position.second) >= 2 && board_.getCell(new_position.first, new_position.second) <= 5;
            nastreljane_pozicije.insert(new_position);
            lastMove = new_position;
            return new_position;
        }
    }

    // nismo še streljali
    std::pair<int, int> random_position = generateRandomPosition();
    nastreljane_pozicije.insert(random_position);
    targeted_positions = getAdjacentNonHitPositions(random_position.first, random_position.second, nastreljane_pozicije);
    wasLastHit = board_.getCell(random_position.first, random_position.second) >= 2 && board_.getCell(random_position.first, random_position.second) <= 5;
    lastMove = random_position;
    return random_position;
}

/*To funkcijo uporabimo za postavitev ladjic na polje. Vrniti moramo Board, ki predstavlja naše polje. Ladjice na polje postavljamo naključno, pri tem pa moramo
upoštevati, da imamo 5 ladjic velikosti 5, 4, 3, 3 in 2. Te se med sabo ne smejo dotikati, lahko pa jih postavljamo horizontalno ali navpično. Začnemo postavljati
na vedno drugi random poziciji x, y, random določimo tudi prvo ladjico in njeno orientacijo (navpično ali horizontalno).*/

Board s23232067::PlayerStudent::setupBoard()
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
void s23232067::PlayerStudent::logMoveResult(int x, int y)
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

void s23232067::PlayerStudent::logOpponentMove(int x, int y) {}

// Funkcija, ki preveri ali se ladje med sabo dotikajo. V primeru, da se dotikajo vrne false, v primeru, da se ne dotikajo vrne true.
bool s23232067::PlayerStudent::notTouch(int x, int y, int shipLength, Orientation orientation, Board board_)
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

// std::pair<int, int> s23232067::PlayerStudent::getMove() {

//     std::cout << "Smo v Leja::getMove()" << std::endl;

//     //Ustvarimo prazno množico v katero bomo shranjevali pozicije na katere smo že streljali
//     std::set<std::pair<int, int>> nastreljane_pozicije;

//     //Ustvarimo random par števil x in y, ki predstavljata prvo pozicijo na katero želimo streljati in jo ciljamo ter jo nato dodamo v množico že streljanih pozicij
//     int x = dist_(gen_);
//     int y = dist_(gen_);
//     std::pair<int, int> prva_pozicija = std::make_pair(x, y);
//     nastreljane_pozicije.insert(prva_pozicija);

//     int x_p = x;
//     int y_p = y;

//     /*Če smo zadeli, potem streljamo na pozicijo levo od prve pozicije, preverimo ali smo to pozicijo že streljali, če smo, se pomaknemo v desno, dokler ne najdemo pozicije,
//     ki je še nismo streljali*/
//     bool result_ = board_.markHit(x, y);
//     bool x_minus = false;
//     bool x_plus = false;
//     bool y_minus = false;
//     bool y_plus = false;

//     std::cout << result_ << std::endl;

//    if (result_ == true && x_minus == false && x_plus == false && y_minus == false && y_plus == false){
//         x_minus = true;
//         while (nastreljane_pozicije.find(std::make_pair(x, y)) != nastreljane_pozicije.end() && x > 0 && x_minus == true){
//             x--;
//             std::cout << "x--" << std::endl;
//             return std::make_pair(x, y);
//             result_ = board_.markHit(x, y);
//             }

//             if (result_ == false && x_minus == true) {
//                 x_plus = true;
//                 x_minus = false;
//                 while (nastreljane_pozicije.find(std::make_pair(x, y)) != nastreljane_pozicije.end() && x < 9 && result_ == true && x_plus == true){
//                     x = x_p;
//                     y = y_p;
//                     x++;
//                     std::cout << "x++" << std::endl;
//                     return std::make_pair(x, y);
//                     result_ = board_.markHit(x, y);
//                 }

//                  if (result_ == false && x_plus == true){
//                     y_minus = true;
//                     x_plus = false;
//                     while (nastreljane_pozicije.find(std::make_pair(x, y)) != nastreljane_pozicije.end() && y > 0 && result_ == true && y_minus == true){
//                         x = x_p;
//                         y = y_p;
//                         y--;
//                         std::cout << "y--" << std::endl;
//                         return std::make_pair(x, y);
//                         result_ = board_.markHit(x, y);
//                     }

//                         if (result_ == false && y_minus == true){
//                             y_plus = true;
//                             y_minus = false;
//                             while (nastreljane_pozicije.find(std::make_pair(x, y)) != nastreljane_pozicije.end() && y < 9 && result_ == true && y_plus == true){
//                                 x = x_p;
//                                 y = y_p;
//                                 y++;
//                                 std::cout << "y++" << std::endl;
//                                 return std::make_pair(x, y);
//                                 result_ = board_.markHit(x, y);
//                             }
//                         }
//                         else{
//                         std::cout << "Napaka pri streljanju." << std::endl;
//                         //V tem primeru vrnemo random pozicijo, preverimo pa, da še ni bila uporabljena
//                         while (nastreljane_pozicije.find(std::make_pair(x, y)) != nastreljane_pozicije.end()){
//                             x = dist_(gen_);
//                             y = dist_(gen_);
//                             return std::make_pair(x, y);
//                             x_minus = false;
//                             x_plus = false;
//                             y_minus = false;
//                             y_plus = false;
//                             result_ = board_.markHit(x, y);
//                         }
//                         }
//                 }
//             }
//     }

//     //Vrnemo par števil x in y, ki predstavljata pozicijo na katero želimo streljati
//     return std::make_pair(x, y);
// }
