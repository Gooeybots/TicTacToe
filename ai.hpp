#ifndef AI_HPP
#define AI_HPP

#include <array>

namespace AI {
    // returns the best move found
    int Move(std::array<int, 9> board, int player);
    // returns the score for the move
    int MiniMax(std::array<int, 9> board, int player);
    // returns the player to win or 0
    int Win(const std::array<int, 9> board);
}

#endif // AI_HPP
