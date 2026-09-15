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

//TODO: remove fast, only temporary
struct Color {
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};

class IElement {
    public:
        virtual ~IElement() = default;

        Transform transform;
        int zIndex = 0;

        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
};

}

#endif /* IELEMENT_HPP_ */
