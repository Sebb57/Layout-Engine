/**
 * @file addElement.cpp
 * @brief section method to add element to its map
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "IElement.hpp"
#include "Section.hpp"
#include <memory>

bool Layout::Section::addElement(std::string name, std::unique_ptr<IElement> element)
{
    if (!element)
        return false;
    return this->_elementMap.emplace(name, std::move(element)).second;
}
