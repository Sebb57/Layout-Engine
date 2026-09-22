/**
 * @file addElement.cpp
 * @brief layout addElement method
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"
#include <memory>

void Layout::Layout::addElem(std::unique_ptr<IElement> element, std::string elemId, std::string secId)
{
    if (!element || this->_sections.find(secId) == this->_sections.end())
        return;
    this->_sections.at(secId)->addElement(elemId, std::move(element));
}
