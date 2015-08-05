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
    bool won(false);
    if(!won)
    {
        for(std::size_t i(0); i < mBoard.size(); i += 3)
        {
            if(mBoard[i] == mBoard[i+1] && mBoard[i+1] == mBoard[i+2] &&
                    mBoard[i] != 0)
            {
                winner = mBoard[i];
                won = true;
            }
        }
    }
    if(!won)
    {
        for(std::size_t i(0); i < 3; ++i)
        {
            if(mBoard[i] == mBoard[i+3] && mBoard[i+3] == mBoard[i+6] &&
                    mBoard[i] != 0)
            {
                winner = mBoard[i];
                won = true;
            }
        }
    }
    if(!won)
    {
        if(mBoard[4] != 0 &&
                ((mBoard[0] == mBoard[4] && mBoard[4] == mBoard[8]) ||
                (mBoard[2] == mBoard[4] && mBoard[4] == mBoard[6])))
        {
            winner = mBoard[4];
            won = true;
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
