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
#include <memory>

namespace Layout {

class Section {
    std::unordered_map<std::string, std::unique_ptr<IElement>> _elementMap;
    std::string _id;
    bool _hidden;

    public:
        Transform transform;

        std::string getData(std::string id);
        //bool draw(GraphicalHook);
        
        void open() { this->_hidden = !this->_hidden; }
};

}

#endif /* SECTION_HPP_ */

