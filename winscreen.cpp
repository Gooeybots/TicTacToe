#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gameenums.hpp"
#include "winscreen.hpp"
#include "mousekeyboard.hpp"
#include "draw.hpp"

bool BUTTONPRESSED(false);

unsigned int WhereOnScreen();
void KeyPress(GLFWwindow * window, int key, int scancode, int action, int mods);
void MousePress(GLFWwindow * window, int button, int action, int mods);
bool ClickedYesNo(bool down);

bool ShowWinScreen(const std::map<Game, unsigned int> &gameGLObjectMap,
                   const glm::mat4 &viewArea, const float playAreaSquare, int player)
{
    Game textureEnum;
    glm::vec3 colour;

    if(player == 0)
    {
        textureEnum = Game::tiedTexture;
        colour = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    else if(player == 1)
    {
        textureEnum = Game::playerOneWinTexture;
        colour = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else
    {
        textureEnum = Game::playerTwoWinTexture;
        colour = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    while(!BUTTONPRESSED && !glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Draw(gameGLObjectMap, Game::boardVao, Game::withTextureProgram,
             glm::vec2(0.0f, 0.0f), colour, viewArea, textureEnum);

        glfwSetKeyCallback(glfwGetCurrentContext(), KeyPress);
        glfwSetMouseButtonCallback(glfwGetCurrentContext(), MousePress);

        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
    if(BUTTONPRESSED)
    {
        glfwSetKeyCallback(glfwGetCurrentContext(), NULL);
        glfwSetMouseButtonCallback(glfwGetCurrentContext(), NULL);
        BUTTONPRESSED = false;
        return PlayAgain(gameGLObjectMap, viewArea, playAreaSquare);
    }
    return false;
}

bool PlayAgain(const std::map<Game, unsigned int> &gameGLObjectMap,
               const glm::mat4 &viewArea, const float playAreaSquare)
{
    float quarter(playAreaSquare / 4.0f);
    glm::vec2 playTextOffset(quarter, quarter * 2);
    glm::vec2 yesTextOffset(0.0f, quarter);
    glm::vec2 noTextOffset(quarter * 2, quarter);
    glm::vec3 blackColour(0.0f, 0.0f, 0.0f);
    glm::vec3 redColour(1.0f, 0.0f, 0.0f);
    bool buttonPressed(false);

    while(!glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        unsigned int where(WhereOnScreen());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Draw(gameGLObjectMap, Game::textVao, Game::withTextureProgram,
             playTextOffset, blackColour, viewArea, Game::playAgainTexture);
        Draw(gameGLObjectMap, Game::textVao, Game::withTextureProgram,
             yesTextOffset, where == 1 ? redColour : blackColour, viewArea,
             Game::yesTexture);
        Draw(gameGLObjectMap, Game::textVao, Game::withTextureProgram,
             noTextOffset, where == 2 ? redColour : blackColour, viewArea,
             Game::noTexture);
        if(!buttonPressed)
            buttonPressed = ClickedYesNo(buttonPressed);
        else if(buttonPressed && ClickedYesNo(buttonPressed) &&
                where > 0)
        {
            return (where == 1 ? true : false);
        }
        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
    return false;
}

unsigned int WhereOnScreen()
{
    glm::ivec2 mousePos(GetMousePos());
    int topBorder(0), bottomBorder(0), leftBorder(0), rightBorder(0), middle(0);
    unsigned int where(0);

    GetBorders(leftBorder, rightBorder, topBorder, bottomBorder, middle, 2);
    middle += leftBorder;
    if(!(mousePos.x < leftBorder || mousePos.y > rightBorder ||
         mousePos.y < topBorder || mousePos.y > bottomBorder))
    {
        if(mousePos.x > leftBorder && mousePos.x < middle)
            where = 1;
        else if(mousePos.x > middle && mousePos.x < rightBorder)
            where = 2;
    }
    return where;
}

void KeyPress(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        BUTTONPRESSED = true;
// Just to ditch unused var message
    else if(window && key && scancode && mods)
        return;
}

void MousePress(GLFWwindow *window, int button, int action, int mods)
{
    if(action == GLFW_RELEASE)
        BUTTONPRESSED = true;
// Just to ditch unused var message
    else if(window && button && mods)
        return;
}
