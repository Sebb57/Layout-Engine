/**
 * @file openSection.cpp
 * @brief layout open section private method
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"

void Layout::Layout::openSection(std::string target)
{
    if (this->_sections.find(target) == this->_sections.end())
        return;
    this->_sections.at(target)->open();
}
