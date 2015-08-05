#ifndef WINSCREEN_HPP
#define WINSCREEN_HPP

#include <map>
#include <glm/glm.hpp>
#include "gameenums.hpp"

bool ShowWinScreen(const std::map<Game, unsigned int> &GameGLObjectMap,
                   const glm::mat4 &viewArea, const float playAreaSquare,
                   int player = 0);
bool PlayAgain(const std::map<Game, unsigned int> &GameGLObjectMap,
               const glm::mat4 &viewArea, const float playAreaSquare);

#endif // WINSCREEN_HPP
