/**
 * @file section.cpp
 * @brief inherited function
 *
 * @author Seb
 * @date 2026-09-17
**/

#include "Section.hpp"
#include "Layout.hpp"

void Layout::Section::update(float deltaTime)
{
    (void)deltaTime;

    for (auto element: this->_elementSorted)
        this->_elementMap[element.second]->update(0); // TODO: deltaTime
}

void Layout::Section::draw(IGraphic& graphicalLib)
{
    if (!this->_hidden)
        graphicalLib.drawRectangle(this->transform, this->_options);
}
