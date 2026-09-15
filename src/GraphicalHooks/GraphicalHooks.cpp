/**
 * @file GraphicalHooks.cpp
 * @brief Graphical Hooks
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#include "GraphicalHooks.hpp"

void Layout::GraphicalHooks::drawRect(Transform transform)
{
    if (this->_drawRect.has_value())
        this->_drawRect.value()(transform);
}

void Layout::GraphicalHooks::drawImage(Transform transform)
{
    if (this->_drawImage.has_value())
        this->_drawImage.value()(transform);
}

void Layout::GraphicalHooks::drawText(Transform transform)
{
    if (this->_drawText.has_value())
        this->_drawText.value()(transform);
}
