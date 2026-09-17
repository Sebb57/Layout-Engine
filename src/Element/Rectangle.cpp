/**
 * @file Rectangle.cpp
 * @brief rectangle class implementation
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Rectangle.hpp"
#include <memory>

Layout::Rectangle::Rectangle(Transform transform, Options options) : AElement(transform, options)
{}

void Layout::Rectangle::update(float deltaTime)
{
    (void)deltaTime;
}

void Layout::Rectangle::draw(IGraphic& graphicalLib)
{
    graphicalLib.drawRectangle(this->transform, this->_options);
}
