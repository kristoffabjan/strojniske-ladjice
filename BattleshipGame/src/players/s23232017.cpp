#include <cstdlib> // For rand()
#include <ctime>   // For time()
#include <iostream>
#include <utility>
#include <random>
#include "../../include/players/s23232017.h"
#include <set>
#include <unordered_set>    
#include <algorithm>

// <-- SETTINGS -->

//DEBUGGING MODE
bool debug = false;

//EXPERIMENTAL MODE
bool experimental = true;


// <-- CODE LOGIC START -->

//Hit old moves
bool old_moves_log = true; //If true, it will not clear hitCells every turn (so it can remember previous hits) - clear after failed
bool hit_old_moves = true; 





s23232017::PlayerStudent::PlayerStudent() : Player("32017")
{
    gen_.seed(std::random_device()());
    dist_ = std::uniform_int_distribution<int>(0, 9);
}

std::pair<int, int> s23232017::PlayerStudent::getMove()
{
    int x, y;
    std::pair<int, int> move;

    /*
    Logic for hitting:
    1. Check old moves from last run. When the first miss will be logged using this strategy, hit_old_moves will be set to false.  
        There is aditional checking to make sure that the move is not in targetedCells (so it is not repeated).

    2. Second strategy is to hit cells from toBeHit. When a cell is hit, all surrounding cells are added to toBeHit. In log function there is also a logic (experimental) that
        checks orientation of the ship and eliminates unnecessary cells from toBeHit.
    
    3. If toBeHit is empty, generate random coordinates, while checking if they are not in targetedCells (so they are not repeated). When hit, 
        second strategy will be used again.
    */

    //First strategy
    if (old_moves.size() > 0 && hit_old_moves) 
    {
            bool foundTargeted = false;
            bool foundMiss = false;
        
        do{
            move = *old_moves.begin();
            old_moves.erase(old_moves.begin());
        }
        while (std::find(targetedCells.begin(), targetedCells.end(), move) != targetedCells.end());

    }

    else{

        //Second strategy
        if(toBeHit.size() > 0){
            move = *toBeHit.begin();
            toBeHit.erase(toBeHit.begin());
        }

        else{
            //Third strategy
            int tryCount = 1000; //Prevent looping forever (will be forced to take random guess)
            do{
                x = dist_(gen_);
                y = dist_(gen_);
                tryCount--;
            }
            while (std::find(targetedCells.begin(), targetedCells.end(), std::make_pair(x, y)) != targetedCells.end() || !tryCount);
            move = std::make_pair(x, y);
        }
    }

    //Add to targetedCells (so it is not repeated)
    targetedCells.insert(move);
    return move;
}

Board s23232017::PlayerStudent::setupBoard()
{
    board_.clearBoard();
    
    //Clear sets
    targetedCells.clear();

    if(old_moves_log){
        old_moves = hitCells;
        old_miss = miss;
        hit_old_moves = true;
        
    }
    hitCells.clear();
    miss.clear();
    toBeHit.clear();
    doNotGuess.clear();

    for (int shipSize : shipSizes)
    {
        //Randomly generate x and y coordinates
        int x = dist_(gen_); 
        int y = dist_(gen_);

        //Randomly generate orientation
        Orientation orientation = static_cast<Orientation>(dist_(gen_) % 2);

        //Place ship (try again if it fails)
        int fail_count = 0;

        while(!board_.isValidPosition(x, y, shipSize, orientation) || !notTouching(x, y, shipSize, orientation, board_))
        {
            x = dist_(gen_); 
            y = dist_(gen_);
            orientation = static_cast<Orientation>(dist_(gen_) % 2);

            fail_count++;
            if(fail_count > 1000){
                std::cout << "Failed to place ship ... running setup process again" << std::endl;
                board_.clearBoard();
                setupBoard();
            }
        }


        board_.placeShip(x, y, shipSize, orientation);

  

    }
    return board_;
}


void s23232017::PlayerStudent::logMoveResult(int x, int y, bool result) {

    //Store hit
    std::pair<int, int> hit = std::make_pair(x, y);

    if (result){
        //If hit, add to hitCells and toBeHit
        hitCells.insert({hit});
    
        //Add surrounding cells to toBeHit
        for (int ix = 0; ix < 3; ix++)
        {
            for (int iy = 0; iy < 3; iy++)
            {
                int x_ = x - 1 + ix;
                int y_ = y - 1 + iy;
                //check if out of bounds
                if (x_ < 0 || x_ > 9 || y_ < 0 || y_ > 9)
                {
                    continue;
                }

                //do not include if has already been targeted
                if (std::find(targetedCells.begin(), targetedCells.end(), std::make_pair(x_, y_)) != targetedCells.end())
                {
                    continue;
                }
                toBeHit.insert(std::make_pair(x_, y_));
                

            }
        }


        //Check if adjacent to last hit and determine orientation
        if (hit.second == lastToBeHit.second && (hit.first == lastToBeHit.first + 1 || hit.first == lastToBeHit.first - 1)){
            //Same x, vertical
            //Remove left and right of this and previous cell
            //std::cout << "Vertical" << std::endl;
            
            int hit_minus = hit.second - 1;
            int hit_plus = hit.second + 1;
            int last_minus = lastToBeHit.second - 1;    
            int last_plus = lastToBeHit.second + 1;

            //Check if out of bounds
            if(hit_minus < 0 || hit_minus > 9 || hit_plus < 0 || hit_plus > 9 || last_minus < 0 || last_minus > 9 || last_plus < 0 || last_plus > 9){
                //Nothing
            }
            else{
                //Add to doNotGuess - for debugging
                if (debug){
                    doNotGuess.insert(std::make_pair(hit.first, hit_minus));
                    doNotGuess.insert(std::make_pair(hit.first, hit_plus));
                    doNotGuess.insert(std::make_pair(lastToBeHit.first, last_minus));
                    doNotGuess.insert(std::make_pair(lastToBeHit.first, last_plus));
                }

                //Erase from toBeHit
                toBeHit.erase(std::make_pair(hit.first, hit_minus));
                toBeHit.erase(std::make_pair(hit.first, hit_plus));
                toBeHit.erase(std::make_pair(lastToBeHit.first, last_minus));
                toBeHit.erase(std::make_pair(lastToBeHit.first, last_plus));

                //Add to targetedCells - so it is not inclulded in random hitting
                targetedCells.insert(std::make_pair(hit.first, hit_minus));
                targetedCells.insert(std::make_pair(hit.first, hit_plus));
                targetedCells.insert(std::make_pair(lastToBeHit.first, last_minus));
                targetedCells.insert(std::make_pair(lastToBeHit.first, last_plus));

            }

        }
        else if (hit.first == lastToBeHit.first && (hit.second == lastToBeHit.second + 1 || hit.second == lastToBeHit.second - 1)){
            //Same x, horizontal
            //Remove up and down of this and previous cell
            //std::cout << "Horizontal" << std::endl;

            int hit_minus = hit.first - 1;
            int hit_plus = hit.first + 1;
            int last_minus = lastToBeHit.first - 1;
            int last_plus = lastToBeHit.first + 1;

            //Check if out of bounds
            if(hit_minus < 0 || hit_minus > 9 || hit_plus < 0 || hit_plus > 9 || last_minus < 0 || last_minus > 9 || last_plus < 0 || last_plus > 9){
                //Nothing
            }
            else{
                //Add to doNotGuess - for debugging
                if (debug){
                    doNotGuess.insert(std::make_pair(hit_minus, hit.second));
                    doNotGuess.insert(std::make_pair(hit_plus, hit.second));
                    doNotGuess.insert(std::make_pair(last_minus, lastToBeHit.second));
                    doNotGuess.insert(std::make_pair(last_plus, lastToBeHit.second));
                }

                //Erase from toBeHit
                toBeHit.erase(std::make_pair(hit_minus, hit.second));
                toBeHit.erase(std::make_pair(hit_plus, hit.second));
                toBeHit.erase(std::make_pair(last_minus, lastToBeHit.second));
                toBeHit.erase(std::make_pair(last_plus, lastToBeHit.second));

                //Add to targetedCells - so it is not inclulded in random hitting
                targetedCells.insert(std::make_pair(hit_minus, hit.second));
                targetedCells.insert(std::make_pair(hit_plus, hit.second));
                targetedCells.insert(std::make_pair(last_minus, lastToBeHit.second));
                targetedCells.insert(std::make_pair(last_plus, lastToBeHit.second));


            }
        }
        
        

        //Store last toBeHit
        lastToBeHit = hit;
    }
    else{
        hit_old_moves = false; //If it misses, start hitting randomly
        miss.insert({hit}); //Add to old misses
    }


}
void s23232017::PlayerStudent::logOpponentMove(int x, int y) {}

//Function to check if ship is not touching another ship (left, right and diagonals) - WORKING GREAT
bool s23232017::PlayerStudent::notTouching(int x, int y, int shipLength, Orientation orientation, Board board_){

    if (orientation == Orientation::Horizontal)
    {
        for (int ix = 0; ix < 3; ix++)
        {
            for (int iy = 0; iy < shipLength + 2; iy++)     
            {
                int x_ = x - 1 + ix;
                int y_ = y - 1 + iy;
                //check if out of bounds
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
    { // orientation == Orientation::Vertical
        for (int ix = 0; ix < shipLength + 2; ix++)
        {
            for (int iy = 0; iy < 3; iy++)
            {
                int x_ = x - 1 + ix;
                int y_ = y - 1 + iy;
                //check if out of bounds
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