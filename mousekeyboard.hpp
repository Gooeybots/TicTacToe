#ifndef MOUSEKEYBOARD_HPP
#define MOUSEKEYBOARD_HPP

#include <glm/glm.hpp>

glm::ivec2 GetMousePos();
void GetBorders(int &left, int &right, int &top, int &bottom, int &bottomMid,
                int &topMid, int &leftMid, int &rightMid, const int divisor);
void GetBorders(int &left, int &right, int &top, int &bottom, int &middle, const int divisor);
#endif // MOUSEKEYBOARD_HPP
