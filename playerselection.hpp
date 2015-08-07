#ifndef PLAYERSELECTION_HPP
#define PLAYERSELECTION_HPP

bool ShowPlayerSelection(
        Board &gameBoard, const glm::mat4 &viewArea, const float playAreaSquare,
        const std::map<Game, unsigned int> &gameGLObjectMap);

#endif // PLAYERSELECTION_HPP
