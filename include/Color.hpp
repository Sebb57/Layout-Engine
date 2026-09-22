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
    float a = 255;
    Color(float r, float g, float b, float a = 255) : r(r), g(g), b(b), a(a) {}
};

} // namespace Layout

#endif /* COLOR_HPP_ */

