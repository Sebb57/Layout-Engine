/**
 * @file Color.hpp
 * @brief color class
 *
 * @author Seb
 * @date 2026-09-16
**/

#ifndef COLOR_HPP_
#define COLOR_HPP_

namespace Layout {

struct Color {
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;
    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};

}

#endif /* COLOR_HPP_ */

