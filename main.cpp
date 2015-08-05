#include <iostream>
#include <exception>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include "setupgame.hpp"

int main()
{
    if(SetupWindow("Tic-Tac-Toe", 500, 500))
        SetupGame();

    return 0;
}
