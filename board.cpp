#include <array>
#include "board.hpp"

Board::Board()
{
    mBoard.fill(0);
}

void Board::ResetBoard()
{
    mBoard.fill(0);
}

bool Board::SetSquare(const std::size_t pos, const int player)
{
    if(pos < mBoard.size() && mBoard[pos] == 0)
    {
         mBoard[pos] = player;
        return true;
    }

    return false;
}

bool Board::GetWin(int &winner) const
{
    // All possible wins
    static int winLines[8][3] =
    {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    bool won(false);

    for(int i(0); i < 8; ++i)
    {
        if(mBoard[winLines[i][0]] > 0 &&
                mBoard[winLines[i][0]] == mBoard[winLines[i][1]] &&
                mBoard[winLines[i][1]] == mBoard[winLines[i][2]])
        {
            winner = mBoard[winLines[i][0]];
            won = true;
            break;
        }
    }

    return won;
}

bool Board::BoardFull() const
{
    bool full(true);
    for(std::size_t i(0); i < mBoard.size(); i++)
    {
        if(mBoard[i] == 0)
        {
            full = false;
            break;
        }
    }
    return full;
}

int Board::GetSquare(const std::size_t pos) const
{
    if(pos < mBoard.size())
        return mBoard[pos];
    return -1;
}

std::array<int, 9> Board::GetBoard()
{
    return mBoard;
}
