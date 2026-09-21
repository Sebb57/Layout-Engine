/**
 * @file popElement.cpp
 * @brief section popElement method
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Section.hpp"

void Layout::Section::popElement(std::string name)
{
    if (this->_elementMap.find(name) == this->_elementMap.end())
        return;
    this->_elementMap.erase(name);
    for (int i = 0; this->_elementSorted.begin() + i != this->_elementSorted.end(); i++) {
        if ((this->_elementSorted.begin() + i)->second == name) {
            this->_elementSorted.erase(this->_elementSorted.begin() + i);
            return;
        }
    }
}
