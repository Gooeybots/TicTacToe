#ifndef WINSCREEN_HPP
#define WINSCREEN_HPP

#include <map>
#include <glm/glm.hpp>
#include "gameenums.hpp"
/* shows a screen with game result until a button is pressed or
 * mouse button clicked */
bool ShowWinScreen(const std::map<Game, unsigned int> &GameGLObjectMap,
                   const glm::mat4 &viewArea, const float playAreaSquare,
                   int player = 0);
/* Asks if you want another game and either restarts game or
 * closes the game */
bool PlayAgain(const std::map<Game, unsigned int> &GameGLObjectMap,
               const glm::mat4 &viewArea, const float playAreaSquare);

#endif // WINSCREEN_HPP
