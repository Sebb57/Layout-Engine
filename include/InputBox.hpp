/**
 * @file InputBox.hpp
 * @brief Input Box Class Header
 *
 * @author SkyReox
 * @date 2026-09-22
**/

#pragma once
#ifndef INPUTBOX_HPP_
    #define INPUTBOX_HPP_

    #include "AElement.hpp"
    #include <iostream>

namespace {

inline constexpr float TEXT_SIZE_MULTIPLIER = 0.35;

}

namespace Layout {

class InputBox : public AElement {
    Transform _textTransform;
    Options _textOptions;
    std::pair<unsigned, unsigned> _windowSize;
    std::string _value;

    void _updateTransforms()
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
        this->_textOptions.primaryColor = Color(255, 255, 255, 255);
    }

    public:
        InputBox(std::string value, Transform transform, Options options) : AElement(transform, options), _textTransform(transform), _value(value) {}
        ~InputBox() = default;

        bool handleEvent(Event event) override { (void) event; return false; }
        void update(float deltaTime) override { (void) deltaTime; }
        void draw(IGraphic& graphicalLib) override
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
        [[nodiscard]] std::string getData() const noexcept final { return this->_value; }
};

}

#endif /* INPUTBOX_HPP_ */
