/**
 * @file Text.cpp
 * @brief text class implementation
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Text.hpp"
#include <memory>

Layout::Text::Text(std::string content, Transform transform, Options options)
    : AElement(transform, options), _content(content)
{}

void Layout::Text::update(float deltaTime)
{
    (void)deltaTime;
}

void Layout::Text::draw(IGraphic& graphicalLib)
{
    graphicalLib.drawText(this->transform, this->_content, this->_options);
}
