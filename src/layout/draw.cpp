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
    if (!this->_graphicalLib)
        return;

    if (!this->_graphicalLib->isOpen())
        this->_graphicalLib->open(this->_width, this->_height, "Layout Engine");

    this->_graphicalLib->clear();
    for (auto& section : this->_sections) {
        section.second->draw(*this->_graphicalLib);

        auto& map = section.second->getElementsMap();
        for (auto& element : section.second->getElementsSorted()) {
            std::cout << element.second << std::endl;
            map.at(element.second)->draw(*this->_graphicalLib);
        }
    }
    this->_graphicalLib->update();
}
