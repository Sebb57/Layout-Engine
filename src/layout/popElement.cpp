/**
 * @file popElement.cpp
 * @brief popElement method for layout
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"

void Layout::Layout::popElem(std::string elemId, std::string secId)
{
    if (this->_sections.find(secId) == this->_sections.end())
        return;
    this->_sections.at(secId)->popElement(elemId);
}

