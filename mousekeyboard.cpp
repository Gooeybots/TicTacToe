#include <GLFW/glfw3.h>
#include "mousekeyboard.hpp"

glm::ivec3 GetWindowOffsetWithDivision(const int divisior);

glm::ivec2 GetMousePos()
{
    double x(0.0), y(0.0);
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    return glm::ivec2((int)x, (int)y);
}

void GetBorders(int &left, int &right, int &top, int &bottom,
                int &bottomMid, int &topMid, int &leftMid, int &rightMid,
                const int divisor)
{
    glm::ivec3 windowOffsetSize(GetWindowOffsetWithDivision(divisor));
    int windowDrawSize(windowOffsetSize.z * divisor);
    GetBorders(left, right, top, bottom, topMid, divisor);

    leftMid = windowOffsetSize.x + windowOffsetSize.z;
    rightMid = windowDrawSize - windowOffsetSize.z + windowOffsetSize.x;
    topMid = windowOffsetSize.y + windowOffsetSize.z;
    bottomMid = windowDrawSize - windowOffsetSize.z + windowOffsetSize.y ;
}

void GetBorders(int &left, int &right, int &top, int &bottom, int &middle, const int divisor)
{
    glm::ivec3 windowOffsetSize(GetWindowOffsetWithDivision(divisor));
    int padding(10), windowDrawSize(windowOffsetSize.z * divisor);

    left = padding + windowOffsetSize.x;
    right = windowDrawSize + windowOffsetSize.x - padding;
    top = padding + windowOffsetSize.y;
    bottom = windowDrawSize + windowOffsetSize.y - padding;
    middle = windowDrawSize / 2;
}

void GetBorders(int &left, int &right, int &top, int &bottom, int &middle,
                int &bottomMiddle, int &topMiddle)
{
    glm::ivec3 windowOffsetSize(GetWindowOffsetWithDivision(5));
    GetBorders(left, right, top, bottom, middle, 5);

    topMiddle = top + windowOffsetSize.z;
    bottomMiddle = bottom - windowOffsetSize.z;
}

glm::ivec3 GetWindowOffsetWithDivision(const int divisor)
{
    int width(0), height(0);
    int xOffset, yOffset, third;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    if(width == height)
    {
        xOffset = yOffset = 0;
        third = width / divisor;
    }
    else if(width < height)
    {
        xOffset = 0;
        yOffset = (height - width) / 2;
        third = width / divisor;
    }
    else
    {
        xOffset = (width - height) / 2;
        yOffset = 0;
        third = height / divisor;
    }

    return glm::ivec3(xOffset, yOffset, third);
}

bool ClickedYesNo(bool down)
{
    bool value(false);

    if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_1)
            == GLFW_PRESS && !down)
        value = true;
    else if(glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_1)
            == GLFW_RELEASE && down)
        value = true;

    return value;
}
