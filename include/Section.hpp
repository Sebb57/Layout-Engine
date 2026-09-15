/**
 * @file Section.hpp
 * @brief section class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef SECTION_HPP_
#define SECTION_HPP_

#include "IElement.hpp"
#include <string>
#include <unordered_map>

namespace Layout {

class Section {
    std::unordered_map<std::string, IElement> _elementMap;
    std::string _id;
    bool _hidden;

    public:
        Rect rect;

        std::string getData(std::string id);
        //bool draw(GraphicalHook);
};

}

#endif /* SECTION_HPP_ */

