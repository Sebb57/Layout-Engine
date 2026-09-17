/**
 * @file draw.cpp
 * @brief layout draw function
 *
 * @author Seb
 * @date 2026-09-17
**/

#include "AGraphic.hpp"
#include "Layout.hpp"
#include <memory>

void Layout::Layout::draw()
{
    if (!this->_graphicalLib)
        return;

    if (!this->_graphicalLib->isOpen())
        this->_graphicalLib->open(this->_width, this->_height, "Layout Engine");

    this->_graphicalLib->clear();
    for (auto& section : this->_sections) {
        section.second->draw(*this->_graphicalLib.get());

        for (auto& element : section.second->getElementsMap() ) {
            element.second->draw(*this->_graphicalLib.get());
        }
    }
    this->_graphicalLib->update();
}
