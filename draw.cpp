#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "board.hpp"
#include "draw.hpp"

unsigned int GetDataFromMap(const std::map<Game, unsigned int> &gameGLObjectMap,
                            const Game gameEnum);

void Draw(const std::map<Game, unsigned int> &gameGLObjectMap, const Game vaoEnum,
          const Game programEnum, const glm::vec2 &offset, const glm::vec3 &colour,
          const glm::mat4 &viewArea, const Game textureEnum)
{
    glBindVertexArray(GetDataFromMap(gameGLObjectMap, vaoEnum));

    GLuint program(GetDataFromMap(gameGLObjectMap, programEnum));
    glUseProgram(program);
    glUniform2f(glGetUniformLocation(program, "offset"),
                offset.x, offset.y);
    glUniform3f(glGetUniformLocation(program, "colourIn"),
                colour.x, colour.y, colour.z);
    glUniformMatrix4fv(glGetUniformLocation(program, "view"),
                       1, GL_FALSE, glm::value_ptr(viewArea));

    if(textureEnum != none)
        glBindTexture(GL_TEXTURE_2D, GetDataFromMap(gameGLObjectMap, textureEnum));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
    glBindVertexArray(0);
}

unsigned int GetDataFromMap(const std::map<Game, unsigned int> &gameGLObjectMap,
                            const Game gameEnum)
{
    auto object(gameGLObjectMap.find(gameEnum));
    if(object != gameGLObjectMap.end())
        return object->second;
    return 0;
}
