/**
 * @file GraphicalHooks.hpp
 * @brief graphical hook class for graphical libs
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef GRAPHICALHOOKS_HPP_
#define GRAPHICALHOOKS_HPP_

#include "Component.hpp"
#include <functional>
#include <optional>

namespace Layout {

class GraphicalHooks { //TODO: give them all a opt struct as param to be able to customize them
    LibName _graphicalLib;
    std::optional<std::function<void(Transform)>> _drawRect;
    std::optional<std::function<void(Transform)>> _drawImage;
    std::optional<std::function<void(Transform)>> _drawText;

    public:
        GraphicalHooks(LibName name = LibName::SFML);

        LibName getLibName() { return this->_graphicalLib; }

        void drawRect(Transform);
        void drawImage(Transform);
        void drawText(Transform);

        void attachDrawRect(std::function<void(Transform)> func) { this->_drawRect = func; }
        void attachDrawImage(std::function<void(Transform)> func) { this->_drawImage = func; }
        void attachDrawText(std::function<void(Transform)> func) { this->_drawText = func; }

        void detachDrawRect() { this->_drawRect.reset(); }
        void detachDrawImage() { this->_drawImage.reset(); }
        void detachDrawText() { this->_drawText.reset(); }
};

}

#endif /* GRAPHICALHOOKS_HPP_ */

