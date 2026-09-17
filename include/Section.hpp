/**
 * @file Section.hpp
 * @brief section class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef SECTION_HPP_
#define SECTION_HPP_

#include "AElement.hpp"
#include "IElement.hpp"
#include "constants.hpp"
#include "Color.hpp"
#include <string>
#include <unordered_map>
#include <memory>

namespace Layout {

class Section : public AElement {
    std::unordered_map<std::string, std::unique_ptr<IElement>> _elementMap;
    std::string _id;
    bool _hidden;

    public:
        Section(Transform transform, Color fillColor, Color borderColor,  std::string id, bool hidden, int zIndex = -1) : AElement(transform, fillColor, borderColor, zIndex), _id(id), _hidden(hidden) {}
        ~Section() = default;

        std::unordered_map<std::string, std::unique_ptr<IElement>>& getElementsMap() { return this->_elementMap; }
        std::string getData(std::string id);
        bool addElement(std::string name, std::unique_ptr<IElement> element);
        
        void open() { if (this->_id != constants::mainWindowName) this->_hidden = !this->_hidden; }
        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;

};

}

#endif /* SECTION_HPP_ */

