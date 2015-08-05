#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>

class Board
{
public:
    Board();
    // sets all elements of mBoard to 0
    void ResetBoard();
    // false if pos is out of bounds
    bool SetSquare(const std::size_t pos, const int player);
    // returns true if board is full sets winner to 0 incase of a tie
    bool GetWin(int &winner) const;
    // returns true if it is full
    bool BoardFull() const;
    // returns -1 if the pos is out of bounds
    int GetSquare(const std::size_t pos) const;
private:
    std::array<int, 9> mBoard;
};

#endif // BOARD_HPP
