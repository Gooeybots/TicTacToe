#ifndef MOUSEKEYBOARD_HPP
#define MOUSEKEYBOARD_HPP

#include <glm/glm.hpp>
/* Returns where in the window the mouse is */
glm::ivec2 GetMousePos();
/* returns the borders for left right top bottom bottom middle topmid
 * ect from divisor */
void GetBorders(int &left, int &right, int &top, int &bottom, int &bottomMid,
                int &topMid, int &leftMid, int &rightMid, const int divisor);
/* returns left right top bottom and middle from divisor */
void GetBorders(int &left, int &right, int &top, int &bottom, int &middle, const int divisor);
/* returns borders from a vertical 4 way split */
void GetBorders(int &left, int &right, int &top, int &bottom, int &middle,
                 int &bottomMiddle, int &topMiddle);
/* returns true if mouse1 is pressed or released */
bool ClickedYesNo(bool down);
#endif // MOUSEKEYBOARD_HPP
