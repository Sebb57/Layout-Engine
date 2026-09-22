/**
 * @file addElement.cpp
 * @brief section method to add element to its map
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "IElement.hpp"
#include "Section.hpp"
#include <algorithm>
#include <memory>
#include <utility>

bool Layout::Section::addElement(std::string name, std::unique_ptr<IElement> element)
{
    if (!element)
        return false;

    if (!this->_elementMap.emplace(name, std::move(element)).second)
        return false;
    auto& inserted = this->_elementMap.at(name);

    this->_elementSorted.emplace_back(inserted->getZIndex(),name);
    std::sort(
        this->_elementSorted.begin(),
        this->_elementSorted.end(),
        [](const auto& p, const auto& p2) {
            return p.first < p2.first;
        }
    );

    return true;
}
