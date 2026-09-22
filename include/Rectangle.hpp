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
#include "Options.hpp"
#include <memory>

namespace Layout {

class Rectangle : public AElement {
    public:
        Rectangle(Transform transform, Options options);
        ~Rectangle() = default;

        bool handleEvent(Event event) override { (void) event; return false; }
        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;

        [[nodiscard]] std::string getData() const noexcept final { return ""; }
};

}

#endif /* RECTANGLE_HPP_ */

