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

namespace Layout {

class Rectangle : public AElement {
    public:
        Rectangle(Color fillColor, Color borderColor) : AElement(fillColor, borderColor) {}
        ~Rectangle() = default;

        void update(float deltaTime) override;
        void draw() override;
};

}

#endif /* RECTANGLE_HPP_ */

