#include <iostream>
#include <numeric>
#include <iomanip>
#include <map>
#include <set>
#include <array>
#include "Board.h"

Board::Board()
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = 0;
        }
    }
}

// Place a ship at the given position
// x is the row, y is the column
bool Board::placeShip(int x, int y, int shipLength, Orientation orientation)
{
    if (!isValidPosition(x, y, shipLength, orientation))
    {
        std::cout << "Invalid position for ship of length " << shipLength
                  << " at position (" << x << ", " << y << ")" << std::endl;
        return false;
    }
    if (orientation == Orientation::Horizontal)
    {
        for (int i = 0; i < shipLength; i++)
        {
            board_[x][y + i] = shipLength;
        }
    }
    else
    { // orientation == Orientation::Vertical
        for (int i = 0; i < shipLength; i++)
        {
            board_[x + i][y] = shipLength;
        }
    }
    return true;
}

// Mark the cell as hit and return true if there is a ship at this position
// x is the row, y is the column
bool Board::markHit(int x, int y)
{
    if (board_[x][y] > 1)
    {                     // There is a ship at this position
        board_[x][y] = 1; // Mark hit
        return true;      // Hit a ship
    }
    else if (board_[x][y] == 0)
    {                      // There is no ship at this position
        board_[x][y] = -1; // Mark hit
        return false;      // Hit the water
    }
    return false; // This position has been hit before
}

// Check if the ship can be placed at the given position
// without overlapping with other ships or going out of bounds
// x is the row, y is the column
bool Board::isValidPosition(int x, int y, int shipLength, Orientation orientation) const
{
    // Input Validation: Check if starting coordinates are within the board's bounds
    if (x < 0 || x >= size_ || y < 0 || y >= size_)
    {
        return false;
    }

    if (orientation == Orientation::Vertical)
    {
        // Check if the ship fits within the board horizontally
        if (x + shipLength > size_)
        {
            return false;
        }
        for (int i = -1; i <= shipLength; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // Skip checking outside of the board
                if (x + i < 0 || x + i >= size_ || y + j < 0 || y + j >= size_)
                {
                    continue;
                }
                // Check if cell and adjacent cells are occupied
                if (board_[x + i][y + j] != 0)
                {
                    return false;
                }
            }
        }
    }
    else // Orientation::Horizontal
    {
        // Check if the ship fits within the board vertically
        if (y + shipLength > size_)
        {
            return false;
        }
        for (int i = -1; i <= shipLength; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // Skip checking outside of the board
                if (x + i < 0 || x + i >= size_ || y + j < 0 || y + j >= size_)
                {
                    continue;
                }
                // Check if cell and adjacent cells are occupied
                if (board_[x + i][y + j] != 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::printBoard() const
{
    std::cout << "    ";
    for (int j = 0; j < size_; ++j)
    {
        std::cout << std::setw(2) << j + 1;
    }
    std::cout << "\n\n";

    for (int i = 0; i < size_; ++i)
    {
        std::cout << std::setw(2) << static_cast<char>('A' + i) << "  ";
        for (int j = 0; j < size_; ++j)
        {
            std::cout << std::setw(2) << board_[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool Board::allShipsSunk() const
{
    for (int i = 0; i < size_; ++i)
    {
        for (int j = 0; j < size_; ++j)
        {
            if (board_[i][j] > 0)
            { // There is a ship cell that hasn't been hit
                return false;
            }
        }
    }
    // No ship cells that haven't been hit were found, so all ships must be sunk
    return true;
}

// Check if all ships have been placed by summing all ship cells
bool Board::allShipsPlaced() const
{
    std::vector<int> shipSizes = {5, 4, 3, 3, 2};
    int totalShipCells = std::inner_product(shipSizes.begin(), shipSizes.end(), shipSizes.begin(), 0);

    int currentShipCells = 0;
    for (int i = 0; i < size_; ++i)
    {
        for (int j = 0; j < size_; ++j)
        {
            if (board_[i][j] != 0)
            {
                currentShipCells += board_[i][j];
            }
        }
    }

    return totalShipCells == currentShipCells;
}

// Mark the cell as hit and return true if there is a ship at this position
// x is the row, y is the column
bool Board::applyMove(int x, int y)
{
    if (board_[x][y] > 0)
    {                       // There is a ship at this position
        board_[x][y] *= -1; // Mark the ship cell as hit
        return true;        // Hit a ship
    }
    else if (board_[x][y] == 0)
    {                      // There is no ship at this position
        board_[x][y] = -1; // Mark the cell as hit water
        return false;      // Hit water
    }
    return false; // This position has been hit before
}

int Board::getCell(int x, int y) const
{
    return board_[x][y];
}

bool Board::setCell(int x, int y, int val)
{
    // Check if the cell is valid
    if (x < 0 || x >= size_ || y < 0 || y >= size_)
    {
        return false;
    }
    board_[x][y] = val;
    return true;
}

int Board::getSize() const
{
    return size_;
}

// Check if the board is in a valid state
bool Board::isSetupValid() const
{
    bool visited[10][10] = {};
    std::vector<int> shipCount(6, 0); // shipCount[i] will store count of ships of length i

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (board_[i][j] != 0 && !visited[i][j])
            {
                // Start of a new ship
                int shipLength = board_[i][j];
                int count = 0;
                int dx = 0, dy = 0;

                // Determine the direction of the ship (horizontal or vertical)
                if (j < 9 && board_[i][j + 1] == shipLength)
                    dy = 1; // Horizontal
                else if (i < 9 && board_[i + 1][j] == shipLength)
                    dx = 1; // Vertical

                // Follow the ship and mark cells as visited
                for (int x = i, y = j; x < 10 && y < 10 && board_[x][y] == shipLength; x += dx, y += dy)
                {
                    if (visited[x][y] || (dx == 0 && dy == 0))
                        return false; // Overlapping ship or single cell ship

                    visited[x][y] = true;
                    count++;

                    // Check adjacent cells for other ships
                    for (int adjX = x - 1; adjX <= x + 1; ++adjX)
                    {
                        for (int adjY = y - 1; adjY <= y + 1; ++adjY)
                        {
                            if (adjX >= 0 && adjX < 10 && adjY >= 0 && adjY < 10)
                            {
                                if (board_[adjX][adjY] != 0 && board_[adjX][adjY] != shipLength)
                                    return false; // Adjacent ships
                            }
                        }
                    }
                }

                if (count != shipLength)
                    return false; // Inconsistent ship length

                shipCount[shipLength]++;
            }
        }
    }

    // Check for correct number and size of ships
    // Adjust these values based on the game's rules
    if (shipCount[5] != 1 || shipCount[4] != 1 || shipCount[3] != 2 || shipCount[2] != 1)
        return false;

    return true;
}

void Board::clearBoard()
{
    for (int i = 0; i < size_; i++)
    {
        for (int j = 0; j < size_; j++)
        {
            board_[i][j] = 0;
        }
    }
}
