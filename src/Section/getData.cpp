/**
 * @file getData.cpp
 * @brief section getData method
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Section.hpp"
#include "Text.hpp"

std::string Layout::Section::getData(std::string id)
{
    if (this->_elementMap.find(id) == this->_elementMap.end())
        return "";
    if (Layout::Text* special = dynamic_cast<Layout::Text*>(this->_elementMap.at(id).get())) {
        return special->getContent();
    }
    return "";
}
