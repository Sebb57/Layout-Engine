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

namespace Layout {

class GraphicalHooks { //TODO: give them all a opt struct as param to be able to customize them
    LibName _graphicalLib;

    public:
        GraphicalHooks(LibName name) : _graphicalLib(name) {}

        void drawRect(Rect);
        void drawImage(Rect);
        void drawText(Rect);
};

}

#endif /* GRAPHICALHOOKS_HPP_ */

