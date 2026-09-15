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

namespace Layout {

class IElement {
    public:
        Transform transform;
        int zIndex = 0;

        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
};

}

#endif /* IELEMENT_HPP_ */
