/**
 * @file handleEvent.cpp
 * @brief handleEvent function of Section class
 *
 * @author Alexis
 * @date 2026-09-21
**/

#include "Section.hpp"
#include <iostream>

bool Layout::Section::handleEvent(Event event)
{
    for (auto element: this->_elementSorted)
        if (this->_elementMap[element.second]->handleEvent(event))
            return true;
    return false;
}

bool Layout::Section::isMouseInside(std::pair<int, int> mousePos, std::pair<unsigned, unsigned> windowSize)
{
    int x = windowSize.first * this->transform.Pos.x + this->transform.Pos.offsetX;
    int y = windowSize.second * this->transform.Pos.y + this->transform.Pos.offsetY;
    int w = windowSize.first * this->transform.Size.x + this->transform.Size.offsetX;
    int h = windowSize.second * this->transform.Size.y + this->transform.Size.offsetY;

    if (mousePos.first >= x && mousePos.first < x + w &&
        mousePos.second >= y && mousePos.second < y + h)
        return true;
    return false;
}
