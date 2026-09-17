/**
 * @file Rectangle.cpp
 * @brief rectangle class implementation
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Rectangle.hpp"
#include <memory>

Layout::Rectangle::Rectangle(Transform transform, Color fillColor, Color borderColor, int zIndex) : AElement(transform, fillColor, borderColor, zIndex)
{}

void Layout::Rectangle::update(float deltaTime)
{
    (void)deltaTime;
}

void Layout::Rectangle::draw(IGraphic& graphicalLib)
{
    graphicalLib.drawRectangle(this->transform);
}
