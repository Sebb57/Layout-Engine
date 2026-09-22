/**
 * @file Options.hpp
 * @brief Options Structure
 *
 * @author SkyReox
 * @date 2026-09-17
**/

#pragma once
#ifndef OPTIONS_HPP_
    #define OPTIONS_HPP_

    #include "Color.hpp"

namespace Layout {

struct Options {
    Color primaryColor = { 0, 0, 0, 255 };
    Color secondaryColor = { 255, 255, 255, 255 };
    float outlineThickness = 0.F;
    float angle = 0.F;
    int zIndex = 0;
};

} // namespace Layout

#endif /* OPTIONS_HPP_ */
