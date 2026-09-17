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
#include "constants.hpp"
#include <string>
#include <unordered_map>
#include <memory>

namespace Layout {

class Section {
    std::unordered_map<std::string, std::unique_ptr<IElement>> _elementMap;
    std::string _id;
    bool _hidden;

    public:
        Section(std::string id, bool hidden) : _id(id), _hidden(hidden) {}

        Transform transform;

        std::unordered_map<std::string, std::unique_ptr<IElement>>& getElementsMap() { return this->_elementMap; }
        std::string getData(std::string id);
        bool addElement(std::string name, std::unique_ptr<IElement> element);
        
        void open() { if (this->_id != constants::mainWindowName) this->_hidden = !this->_hidden; }
};

}

#endif /* SECTION_HPP_ */

