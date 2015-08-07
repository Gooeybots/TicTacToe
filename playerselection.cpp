#include <GLFW/glfw3.h>
#include "mousekeyboard.hpp"
#include "draw.hpp"
#include "playgame.hpp"
#include "playerselection.hpp"

int WhereOnScreenNow();

bool ShowPlayerSelection(Board &gameBoard, const glm::mat4 &viewArea,
                         const float playAreaSquare,
                         const std::map<Game, unsigned int> &gameGLObjectMap)
{
    glm::vec3 greenColour(0.0f, 1.0f, 0.0f);
    glm::vec3 redColour(1.0f, 0.0f, 0.0f);
    bool player1(true), player2(true);
    const float quarter(playAreaSquare / 4);

    bool selectionMade(false), buttonPressed(false);
    while(!selectionMade && !glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int where(WhereOnScreenNow());
        for(int i(0); i < 4; ++i)
        {
            Draw(gameGLObjectMap,
                 (i == 0 ? Game::pVPVao :
                           (i == 1 ? Game::pVAiVao :
                                     i == 2 ? Game::aiVPVao :
                                              Game::aiVAiVao)),
                 Game::withTextureProgram,
                 (i == 0 ? glm::vec2(0.0f, quarter * 3.0f) :
                           i == 1 ? glm::vec2(0.0f, quarter * 2.0f) :
                                    i == 2 ? glm::vec2(0.0f, quarter) :
                                             glm::vec2(0.0f, 0.0f)),
                 (where == i ? redColour : greenColour),
                 viewArea, Game::selectionTexture);
        }
        if(!buttonPressed)
            buttonPressed = ClickedYesNo(buttonPressed);
        else if(buttonPressed && ClickedYesNo(buttonPressed) &&
                where >= 0)
        {
            switch(where)
            {
            case 1:
                player2 = false;
                break;
            case 2:
                player1 = false;
                break;
            case 3:
                player1 = player2 = false;
                break;
            default:
                break;
            }
            selectionMade = true;
        }
        glfwSwapBuffers(glfwGetCurrentContext());
        glfwPollEvents();
    }
    if(!selectionMade)
        return false;
    return PlayGame(gameBoard, player1, player2, viewArea, playAreaSquare,
                    gameGLObjectMap);
}

int WhereOnScreenNow()
{
    glm::ivec2 mousePos(GetMousePos());
    int topBorder(0), bottomBorder(0), leftBorder(0), rightBorder(0),
            middleBottom(0), middleTop(0), middle(0);
    int where(-1);

    GetBorders(leftBorder, rightBorder, topBorder, bottomBorder,
               middle, middleBottom, middleTop);

    if(!(mousePos.x < leftBorder || mousePos.y > rightBorder ||
         mousePos.y < topBorder || mousePos.y > bottomBorder))
    {
        if(mousePos.y > topBorder && mousePos.y < middleTop)
            where = 0;
        else if(mousePos.y > middleTop && mousePos.y < middle)
            where = 1;
        else if(mousePos.y > middle && mousePos.y < middleBottom)
            where = 2;
        else if(mousePos.y > middleBottom && mousePos.y < bottomBorder)
            where = 3;
    }
    return where;
}
