#ifndef DRAW_HPP
#define DRAW_HPP

#include <map>
#include <glm/glm.hpp>
#include "gameenums.hpp"

/* Draws the object with all of the given details */
void Draw(const std::map<Game, unsigned int> &gameGLObjectMap, const Game vao,
          const Game program, const glm::vec2 &offset, const glm::vec3 &colour,
          const glm::mat4 &viewArea, const Game texture = Game::none);

#endif // DRAW_HPP
