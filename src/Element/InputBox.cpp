/**
 * @file InputBox.cpp
 * @brief Input Box Class
 *
 * @author SkyReox
 * @date 2026-09-22
**/

#include "InputBox.hpp"

bool Layout::InputBox::handleEvent(Event event)
{
    if (event.type == Event::Type::MouseButtonPressed && event.mouseButton == Event::MouseButton::Left) {
        float w = this->transform.Size.x * this->_windowSize.first + this->transform.Size.offsetX;
        float h = this->transform.Size.y * this->_windowSize.second + this->transform.Size.offsetY;
        float x = this->transform.Pos.x * this->_windowSize.first + this->transform.Pos.offsetX - static_cast<float>(this->transform.AnchX) * w / 2 + static_cast<float>(this->transform.AnchX) / 2 * this->_windowSize.first;
        float y = this->transform.Pos.y * this->_windowSize.second + this->transform.Pos.offsetY -static_cast<float>(this->transform.AnchY) * h / 2 + static_cast<float>(this->transform.AnchY) / 2 * this->_windowSize.second;

        if (event.mouseX >= x && event.mouseX < x + w && event.mouseY >= y && event.mouseY < y + h) {
            this->_selected = true;
            this->_options.secondaryColor = Color(37, 122, 253);
        } else {
            this->_selected = false;
            this->_options.secondaryColor = this->_secondaryColor;
        }
        return false;
    }
    if (this->_selected && event.type == Event::Type::TextEntered) {
        if (event.keyChar == '\b' || event.keyChar == 127) {
            if (!this->_value.empty())
                this->_value.pop_back();
        } else
            this->_value += event.keyChar;
        return true;
    }
    return false;
}

void Layout::InputBox::draw(IGraphic& graphicalLib)
{
    this->_windowSize = graphicalLib.getWindowSize();
    this->_updateTransforms();

    if (this->_value.empty())
        this->_textOptions.primaryColor = Color(180, 180, 180);
    else
        this->_textOptions.primaryColor = Color(255, 255, 255);

    graphicalLib.drawRectangle(this->transform, this->_options);
    graphicalLib.drawText(this->_textTransform, !this->_value.empty() ? this->_value : "Enter text...", this->_textOptions);
}
