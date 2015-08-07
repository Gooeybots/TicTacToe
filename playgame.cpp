#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "board.hpp"
#include "mousekeyboard.hpp"
#include "draw.hpp"
#include "playgame.hpp"
#include "winscreen.hpp"
#include "ai.hpp"

unsigned int UpdateBoard(Board &gameBoard, const unsigned int player,
                         bool realPlayer);
void DrawGame(const Board &gameBoard, const glm::mat4 &viewArea, const float third,
               const std::map<Game, unsigned int> &gameGLObjectMap);
unsigned int GetBoardPosition();
glm::ivec3 GetWindowThirdWithOffset();
glm::vec2 GetBoardOffset(const unsigned int where, const float third);

bool PlayGame(Board &gameBoard, const bool player1, const bool player2,
              const glm::mat4 &viewArea, const float playAreaSquare,
              const std::map<Game, unsigned int> &gameGLObjectMap)
{
    float thirdPlayArea(playAreaSquare / 3.0f);
    int winner(0);
    unsigned int player(1), nextPlayer(1);

    bool gameFinished(false);
    while(!gameFinished && !glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        player = nextPlayer;
        nextPlayer = (player == 1 ?
                          UpdateBoard(gameBoard, player, player1) :
                          UpdateBoard(gameBoard, player, player2));
        DrawGame(gameBoard, viewArea, thirdPlayArea, gameGLObjectMap);

        if(gameBoard.GetWin(winner) || gameBoard.BoardFull())
            gameFinished = true;

        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
    if(!gameFinished)
        return false;

    return ShowWinScreen(gameGLObjectMap, viewArea, playAreaSquare, winner);
}

unsigned int UpdateBoard(Board &gameBoard, const unsigned int player,
                         bool realPlayer)
{
    unsigned int nextPlayer(player);

    if(!realPlayer)
    {
        nextPlayer = (player == 1 ? 2 : 1);
        unsigned int boardPos(AI::Move(gameBoard.GetBoard(), player));
        gameBoard.SetSquare(boardPos, player);
    }
    else
    {
        static bool mouseDown(false);
        unsigned int boardPos(GetBoardPosition());
        GLFWwindow * window(glfwGetCurrentContext());
        if(mouseDown &&
                glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
        {
            mouseDown = false;
            if(gameBoard.SetSquare(boardPos - 1, player) && boardPos > 0)
                nextPlayer = (player == 1 ? 2 : 1);
        }
        else if(!mouseDown &&
                glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
        {
            mouseDown = true;
        }
    }
    return nextPlayer;
}

void DrawGame(const Board &gameBoard, const glm::mat4 &viewArea, const float third,
               const std::map<Game, unsigned int> &gameGLObjectMap)
{
    Draw(gameGLObjectMap, Game::boardVao, Game::boardVao, glm::vec2(0.0f, 0.0f),
         glm::vec3(0.0f, 0.0f, 0.0f), viewArea, Game::boardTexture);

    int boardPos(GetBoardPosition() - 1);
// Draw o and x's also colour square where cursor is
    for(int where(0); where < 9; ++where)
    {
        int player(gameBoard.GetSquare(where));
        if(player == 1 || player == 2)
            Draw(gameGLObjectMap, Game::playerVao,
                 Game::withTextureProgram, GetBoardOffset(where, third),
                 (player == 1 ? glm::vec3(1.0f, 0.0f, 0.0f) :
                                glm::vec3(0.0f, 0.0f, 1.0f)), viewArea,
                 (player == 1 ? Game::xTexture : Game::oTexture));
        else if(boardPos == where)
            Draw(gameGLObjectMap, Game::squareVao, Game::withoutTextureProgram,
                 GetBoardOffset(where, third), glm::vec3(0.0f, 1.0f, 0.0f), viewArea);
    }
}

// returns 0 if there isnt a board pos
unsigned int GetBoardPosition()
{
    glm::ivec2 mousePos(GetMousePos());
    int leftBorder(0), topBorder(0), rightBorder(0), bottomBorder(0),
            leftMidBorder(0), rightMidBorder(0), topMidBorder(0),
            bottomMidBorder(0);
    unsigned int where(0);

    GetBorders(leftBorder, rightBorder, topBorder, bottomBorder, bottomMidBorder,
               topMidBorder, leftMidBorder, rightMidBorder, 3);

    if(!(mousePos.x < leftBorder || mousePos.x >  rightBorder ||
         mousePos.y < topBorder || mousePos.y > bottomBorder))
    {
        if(mousePos.x > leftBorder && mousePos.x < leftMidBorder)
            where = 1;
        else if(mousePos.x > leftMidBorder && mousePos.x < rightMidBorder)
            where = 2;
        else if(mousePos.x < rightBorder && mousePos.x > rightMidBorder)
            where = 3;

        if(where != 0)
        {
            if(mousePos.y > topBorder && mousePos.y < topMidBorder)
                where += 6;
            else if(mousePos.y > topMidBorder && mousePos.y < bottomMidBorder)
                where += 3;
            else if(!(mousePos.y < bottomBorder &&      // If mouse is out of
                      mousePos.y > bottomMidBorder))    // bounds set to 0
                where = 0;
        }
    }
    return where;
}

glm::vec2 GetBoardOffset(const unsigned int where, const float third)
{
    float offsetX(0.0), offsetY(0.0f);
    switch(where)
    {
    case 1:
        offsetX = third;
        break;
    case 2:
        offsetX = third * 2.0f;
        break;
    case 3:
        offsetY = third;
        break;
    case 4:
        offsetX = third;
        offsetY = third;
        break;
    case 5:
        offsetX = third * 2.0f;
        offsetY = third;
        break;
    case 6:
        offsetY = third * 2.0f;
        break;
    case 7:
        offsetX = third;
        offsetY = third * 2.0f;
        break;
    case 8:
        offsetX = third * 2.0f;
        offsetY = third * 2.0f;
        break;
    default:
        break;
    }
    return glm::vec2(offsetX, offsetY);
}
