/**
 * @file IElement.hpp
 * @brief IElement class
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#pragma once
#ifndef IELEMENT_HPP_
    #define IELEMENT_HPP_

    #include "Component.hpp"
    #include "IGraphic.hpp"
    #include <memory>

namespace Layout {

class IElement {
    public:
        virtual ~IElement() = default;

        virtual bool handleEvent(Event event) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw(IGraphic& graphicalLib) = 0;
        [[nodiscard]] virtual std::string getData() const = 0;
        [[nodiscard]] virtual int getZIndex() const noexcept = 0;
};

} // namespace Layout

#endif /* IELEMENT_HPP_ */
