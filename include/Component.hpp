/**
 * @file Component.hpp
 * @brief component structure
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <cstdint>

namespace Layout {

enum class anchorPoints {
    LEFT,
    MID,
    RIGHT
};

struct Rect {
    float x;
    float y;
    uint32_t offsetX;
    uint32_t offsetY;
};

struct Transform {
    anchorPoints AnchX;
    anchorPoints AnchY;
    Rect Pos;
    Rect Size;
};

}

#endif /* COMPONENT_HPP_ */

