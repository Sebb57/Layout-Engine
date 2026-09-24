/**
 * @file InputBox.cpp
 * @brief Input Box Class
 *
 * @author SkyReox
 * @date 2026-09-22
**/

#include "InputBox.hpp"
#include <iostream>

Layout::InputBox::InputBox(std::string value, Transform transform, Options options)
    : AElement(transform, options), _textTransform(transform), _secondaryColor(options.secondaryColor), _value(value)
{
    this->_textOptions.primaryColor = Color(255, 255, 255, 255);

    this->_cursorTransform.AnchX = AnchorX::LEFT;
    this->_cursorTransform.AnchY = AnchorY::TOP;
    this->_cursorOptions.primaryColor = Color(240, 240, 240);
    this->_cursorOptions.outlineThickness = 0;

    this->_cursorChrono = std::make_unique<Chronometer>();
    this->_cursorChrono->reset();
}

void Layout::InputBox::_updateTransforms()
{
    this->_textTransform = this->transform;

    switch (this->transform.AnchX) {
        case AnchorX::LEFT:
            break;
        case AnchorX::MID: 
            this->_textTransform.Pos.x -= this->transform.Size.x / 2;
            this->_textTransform.Pos.offsetX -= this->transform.Size.offsetX / 2;
            break;
        case AnchorX::RIGHT:
            this->_textTransform.Pos.x -= this->transform.Size.x;
            this->_textTransform.Pos.offsetX -= this->transform.Size.offsetX;
            break;
    }
    this->_textTransform.Pos.offsetX += 2;
    switch (this->transform.AnchY) {
        case AnchorY::TOP:
            this->_textTransform.Pos.y += this->transform.Size.y * TEXT_SIZE_MULTIPLIER * 0.5;
            this->_textTransform.Pos.offsetY += this->transform.Size.offsetY * TEXT_SIZE_MULTIPLIER * 0.5;
            break;
        case AnchorY::MID:
            this->_textTransform.Pos.y -= this->transform.Size.y * TEXT_SIZE_MULTIPLIER;
            this->_textTransform.Pos.offsetY -= this->transform.Size.offsetY * TEXT_SIZE_MULTIPLIER;
            break;
        case AnchorY::BOTTOM:
            this->_textTransform.Pos.y -= this->transform.Size.y * (1 - TEXT_SIZE_MULTIPLIER / 2);
            this->_textTransform.Pos.offsetY -= this->transform.Size.offsetY * (1 - TEXT_SIZE_MULTIPLIER / 2);
            break;
    }

    this->_textTransform.Size.x = this->transform.Size.y * TEXT_SIZE_MULTIPLIER;
    this->_textTransform.Size.offsetX = this->transform.Size.offsetY * TEXT_SIZE_MULTIPLIER;
}

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
            this->_showCursor = true;
            this->_cursorChrono->reset();
        } else {
            this->_selected = false;
            this->_options.secondaryColor = this->_secondaryColor;
            this->_showCursor = false;
        }
        return false;
    }
    if (this->_selected && event.type == Event::Type::KeyPressed) {
        if (event.key == Event::Key::Left)
            if (this->_cursorOffset > 0)
                this->_cursorOffset--;
        if (event.key == Event::Key::Right)
            if (this->_cursorOffset < this->_value.length())
                this->_cursorOffset++;
    }
    if (this->_selected && event.type == Event::Type::TextEntered) {
        if (event.keyChar == '\b' || event.keyChar == 127) {
            if (this->_cursorOffset > 0) {
                this->_value.erase(this->_value.begin() + this->_cursorOffset - 1);
                this->_cursorOffset--;
            }
        } else {
            this->_value.insert(this->_value.begin() + this->_cursorOffset, event.keyChar);
            this->_cursorOffset++;
            this->_showCursor = false;
            this->_cursorChrono->reset();
        }
        return true;
    }
    return false;
}

void Layout::InputBox::update(float deltaTime)
{
    (void) deltaTime;

    if (this->_selected) {
        auto elapsedTime = this->_cursorChrono->getElapsedTime();
    
        if (elapsedTime.count() % CURSOR_SWAP*2 >= CURSOR_SWAP) {
            this->_showCursor = !this->_showCursor;
            this->_cursorChrono->reset();
        }
    }
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

    std::string toShow = this->_value;
    if (this->_showCursor) {
        if (toShow.empty())
            toShow = "_";
        else if (this->_cursorOffset == toShow.length())
            toShow += "_";
        else
            toShow[this->_cursorOffset] = '_';
    }
    graphicalLib.drawText(this->_textTransform, this->_selected || !this->_value.empty() ? toShow : "Enter text...", this->_textOptions);
}
