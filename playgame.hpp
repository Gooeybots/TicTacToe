#ifndef PLAYGAME_HPP
#define PLAYGAME_HPP

#include <glm/mat4x4.hpp>
#include <map>
#include "gameenums.hpp"

class Board;
/* Enters a game loop showing the board where everyone is,
 * whos go it is and when its over */
bool PlayGame(Board &gameBoard, unsigned int player, const glm::mat4 &viewArea,
              const float playAreaSquare,
              const std::map<Game, unsigned int> &gameGLObjectMap);

#endif // PLAYGAME_HPP
