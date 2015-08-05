#define GLM_FORCE_RADIANS

#include <iostream>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "setupgame.hpp"
#include "board.hpp"
#include "loadtexture.hpp"
#include "setupprogram.hpp"
#include "gameenums.hpp"
#include "playgame.hpp"

GLuint SetupSquareBuffer(const float size);
GLuint SetupVAOForBufferWithTexture(const GLuint buffer);
GLuint SetupVAOForBufferWithoutTexture(const GLuint buffer);
void AddToMap(std::map<Game, GLuint> &map, const Game gameEnum, const GLuint object);

void SetupGame()
{
    float playingAreaSquare(500.0);

    // Setup player and board
    Board gameBoard;
    unsigned int player(1);

    // Load textures
    GLuint boardTexture(LoadTexture("board.png"));
    GLuint xTexture(LoadTexture("xtexture.png"));
    GLuint oTexture(LoadTexture("otexture.png"));
    GLuint oneWinTexture(LoadTexture("player1win.png"));
    GLuint twoWinTexture(LoadTexture("player2win.png"));
    GLuint tiedTexture(LoadTexture("tied.png"));
    GLuint playAgainTexture(LoadTexture("playagain.png"));
    GLuint yesTexture(LoadTexture("yes.png"));
    GLuint noTexture(LoadTexture("no.png"));

    if(boardTexture == 0 || xTexture == 0 || oTexture == 0 ||
            oneWinTexture == 0 || twoWinTexture == 0 || tiedTexture == 0 ||
            playAgainTexture == 0 || yesTexture == 0 || noTexture == 0)
        return;

    // Setup board and playing square buffers
    GLuint boardBuffer(SetupSquareBuffer(playingAreaSquare));
    GLuint playingSquareBuffer(SetupSquareBuffer(playingAreaSquare / 3.0));
    GLuint textSquareBuffer(SetupSquareBuffer(playingAreaSquare / 2.0));

    // setup the view area
    glm::mat4 viewArea(glm::ortho(
                           0.0f, playingAreaSquare, 0.0f, playingAreaSquare));

    // setup the programs
    GLuint withTexture(SetupProgram("textured.vs", "textured.fs"));
    GLuint withoutTexture(SetupProgram("notexture.vs", "notexture.fs"));

    // setup vaos
    GLuint boardVao(SetupVAOForBufferWithTexture(boardBuffer));
    GLuint playerVao(SetupVAOForBufferWithTexture(playingSquareBuffer));
    GLuint squareVao(SetupVAOForBufferWithoutTexture(playingSquareBuffer));
    GLuint textVao(SetupVAOForBufferWithTexture(textSquareBuffer));

    std::map<Game, GLuint> gameGLObjectMap;
    AddToMap(gameGLObjectMap, Game::boardTexture, boardTexture);
    AddToMap(gameGLObjectMap, Game::xTexture, xTexture);
    AddToMap(gameGLObjectMap, Game::oTexture, oTexture);
    AddToMap(gameGLObjectMap, Game::playerOneWinTexture, oneWinTexture);
    AddToMap(gameGLObjectMap, Game::playerTwoWinTexture, twoWinTexture);
    AddToMap(gameGLObjectMap, Game::tiedTexture, tiedTexture);
    AddToMap(gameGLObjectMap, Game::playAgainTexture, playAgainTexture);
    AddToMap(gameGLObjectMap, Game::yesTexture, yesTexture);
    AddToMap(gameGLObjectMap, Game::noTexture, noTexture);
    AddToMap(gameGLObjectMap, Game::boardVao, boardVao);
    AddToMap(gameGLObjectMap, Game::playerVao, playerVao);
    AddToMap(gameGLObjectMap, Game::squareVao, squareVao);
    AddToMap(gameGLObjectMap, Game::textVao, textVao);
    AddToMap(gameGLObjectMap, Game::withTextureProgram, withTexture);
    AddToMap(gameGLObjectMap, Game::withoutTextureProgram, withoutTexture);

    bool playing(true);
    while(playing && !(glfwWindowShouldClose(glfwGetCurrentContext())))
    {
        playing = PlayGame(gameBoard, player, viewArea, playingAreaSquare, gameGLObjectMap);
        if(!playing)
        {
            gameGLObjectMap.clear();
            glDeleteProgram(withTexture);
            glDeleteProgram(withoutTexture);
            glDeleteTextures(1, &boardTexture);
            glDeleteTextures(1, &xTexture);
            glDeleteTextures(1, &oTexture);
            glDeleteTextures(1, &oneWinTexture);
            glDeleteTextures(1, &twoWinTexture);
            glDeleteTextures(1, &tiedTexture);
            glDeleteTextures(1, &playAgainTexture);
            glDeleteTextures(1, &yesTexture);
            glDeleteTextures(1, &noTexture);
            glDeleteBuffers(1, &boardBuffer);
            glDeleteBuffers(1, &playingSquareBuffer);
            glDeleteBuffers(1, &textSquareBuffer);
            glDeleteVertexArrays(1, &boardVao);
            glDeleteVertexArrays(1, &playerVao);
            glDeleteVertexArrays(1, &squareVao);
            glDeleteVertexArrays(1, &textVao);
            glfwDestroyWindow(glfwGetCurrentContext());
        }
        else
        {
            gameBoard.ResetBoard();
            player = 1;
        }
    }
}

GLuint SetupSquareBuffer(const float size)
{
    if(size > 0.0)
    {
        std::vector<float> positions;
        positions.reserve(24);
        // bottom left
        positions.push_back(0.0f);   positions.push_back(0.0f);
        // bottom right
        positions.push_back(size);   positions.push_back(0.0f);
        // top right
        positions.push_back(size);   positions.push_back(size);
        // bottom left
        positions.push_back(0.0f);   positions.push_back(0.0f);
        // top right
        positions.push_back(size);   positions.push_back(size);
        // top left
        positions.push_back(0.0f);   positions.push_back(size);

positions.push_back(0.0f);   positions.push_back(1.0f);
positions.push_back(1.0f);   positions.push_back(1.0f);
positions.push_back(1.0f);   positions.push_back(0.0f);
positions.push_back(0.0f);   positions.push_back(1.0f);
positions.push_back(1.0f);   positions.push_back(0.0f);
positions.push_back(0.0f);   positions.push_back(0.0f);
        GLuint vbo(0);
        glGenBuffers(1, &vbo);
        if(vbo > 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(),
                         positions.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        else
        {
            std::cerr << "Sorry couldn't create buffer\n";
            vbo = 0;
        }

        positions.clear();

        return vbo;
    }
    return 0;
}

GLuint SetupVAOForBufferWithoutTexture(const GLuint buffer)
{
    GLuint vao(0);
    glGenVertexArrays(1, &vao);

    if(vao == 0)
    {
        std::cerr << "Couldn't create vao\n";
    }
    else
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    return vao;
}

GLuint SetupVAOForBufferWithTexture(const GLuint buffer)
{
    GLuint vao(SetupVAOForBufferWithoutTexture(buffer));
    if(vao > 0)
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glEnableVertexAttribArray(1);
        std::size_t offset(sizeof(float) * 2 * 6);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    return vao;
}

void AddToMap(std::map<Game, GLuint> &map, const Game gameEnum, const GLuint object)
{
    map.insert(std::pair<Game, GLuint>(gameEnum, object));
}
