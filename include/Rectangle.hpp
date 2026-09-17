/**
 * @file Rectangle.hpp
 * @brief rectangle element class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

#include "AElement.hpp"
#include <memory>

namespace Layout {

class Rectangle : public AElement {
    public:
        Rectangle(Transform transform, Color fillColor, Color borderColor, int zIndex = 0);
        ~Rectangle() = default;

        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;
};

}

#endif /* RECTANGLE_HPP_ */

