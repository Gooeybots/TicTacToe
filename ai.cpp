#include "ai.hpp"

namespace AI
{
    int Move(std::array<int, 9> board, int player)
    {
        int move(-1), score(-2);
        for(std::size_t where(0); where < 9; ++where)
        {
            if(board[where] == 0)
            {
                board[where] = player;
                int tempScore(-AI::MiniMax(board, (player == 1 ? 2 : 1)));
                if(tempScore > score)
                {
                    score = tempScore;
                    move = where;
                }
                board[where] = 0;
            }
        }

        if(move == -1)
        {
            return 0;   // Shouldn't ever be reached
        }

        return move;
    }

    int MiniMax(std::array<int, 9> board, int player)
    {
        int score(-2);

        {
            int win(AI::Win(board));
            if(win > 0)
                score = (win == player ? 1 : -1);
        }

        if(score == -2)
        {
            for(std::size_t where(0); where < 9; ++where)
            {
                if(board[where] == 0)
                {
                    board[where] = player;
                    int tempScore(-AI::MiniMax(board, (player == 1 ? 2 : 1)));
                    if(tempScore > score)
                    {
                        score = tempScore;
                    }
                    board[where] = 0;
                }
            }
        }
        if(score == -2)
            return 0;
        return score;
    }

    int Win(const std::array<int, 9> board)
    {
        int won(0);
        static int winLines[8][3] =
        {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };

        for(std::size_t i(0); i < 8; ++i)
        {
            if(board[winLines[i][0]] != 0 &&
                    board[winLines[i][0]] == board[winLines[i][1]] &&
                    board[winLines[i][1]] == board[winLines[i][2]])
            {
                won = board[winLines[i][0]];
                break;
            }
        }
        return won;
    }
}
