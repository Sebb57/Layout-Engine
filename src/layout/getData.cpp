/**
 * @file getData.cpp
 * @brief layout getData method
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"
#include <vector>

std::vector<std::string> Layout::Layout::getData(std::string secId, std::vector<std::string> elemsId)
{
    std::vector<std::string> values;
    if (this->_sections.find(secId) == this->_sections.end() || elemsId.empty())
        return values;

    for (auto& elem : elemsId) {
        for (auto& secElem : this->_sections.at(secId)->getElementsSorted()) {
            if (elem == secElem.second)
                values.push_back(this->_sections.at(secId)->getData(elem));
        }
    }
    return values;
}
