/**
 * @file Text.cpp
 * @brief text class implementation
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Text.hpp"
#include <memory>

Layout::Text::Text(std::string content, Transform transform, Color textColor, unsigned outlineThickness, Color borderColor, int zIndex)
    : AElement(transform, textColor, borderColor, zIndex), _content(content), _textColor(textColor), _outlineThickness(outlineThickness)
{}

void Layout::Text::update(float deltaTime)
{
    (void)deltaTime;
}

void Layout::Text::draw(IGraphic& graphicalLib)
{
    graphicalLib.drawText(this->transform, this->_content);
}
