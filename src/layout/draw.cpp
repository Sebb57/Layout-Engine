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
#include <iostream>

void Layout::Layout::draw()
{
    if (!this->_graphicalLib || !this->_graphicalLib->isOpen())
        return;

    this->_graphicalLib->clear();
    for (auto& section : this->_sections) {
        section.second->draw(*this->_graphicalLib);

        auto& map = section.second->getElementsMap();
        for (auto& element : section.second->getElementsSorted()) {
            map.at(element.second)->draw(*this->_graphicalLib);
        }
    }
    this->_graphicalLib->update();
}
