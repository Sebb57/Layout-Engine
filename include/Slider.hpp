/**
 * @file Slider.hpp
 * @brief Slider Element Class Header
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#pragma once
#ifndef SLIDER_HPP_
    #define SLIDER_HPP_

    #include "AElement.hpp"
    #include "Options.hpp"
    #include <cmath>
    #include <iostream>

namespace Layout {

template <typename T>
class Slider : public AElement {
    Transform _filledTransform;
    Options _filledOptions;
    Transform _handleTransform;
    Options _handleOptions;
    T _value;
    T _min;
    T _max;
    T _step;
    std::pair<unsigned, unsigned> _windowSize;
    std::pair<int, int> _prevMousePos;
    bool _holding = false;

    void _updateTransforms(float filled)
    {
        this->_filledTransform = this->transform;
        this->_handleTransform = this->transform;

        this->_filledTransform.Size.x = this->transform.Size.x * filled;
        this->_filledTransform.Size.offsetX = this->transform.Size.offsetX * filled;

        this->_handleTransform.Size.x = this->transform.Size.y * 0.75 * (static_cast<float>(this->_windowSize.second) / this->_windowSize.first);
        this->_handleTransform.Size.offsetX = this->transform.Size.offsetY * 0.75 * (static_cast<float>(this->_windowSize.second) / this->_windowSize.first);
        this->_handleTransform.Size.y = this->_handleTransform.Size.x;
        this->_handleTransform.Size.offsetY = this->_handleTransform.Size.offsetX;

        this->_handleTransform.Pos.x += this->transform.Size.x * filled;
        this->_handleTransform.Pos.offsetX += this->transform.Size.offsetX * filled;

        switch (this->transform.AnchX) {
            case AnchorX::LEFT:
                this->_handleTransform.Pos.x -= this->_handleTransform.Size.x;
                this->_handleTransform.Pos.offsetX -= this->_handleTransform.Size.offsetX;
                break;
            case AnchorX::MID: 
                this->_filledTransform.Pos.x -= this->transform.Size.x * (1 - filled) / 2;
                this->_filledTransform.Pos.offsetX -= this->transform.Size.offsetY * (1 - filled) / 2;
                this->_handleTransform.Pos.x -= this->transform.Size.x / 2;
                this->_handleTransform.Pos.offsetX -= this->transform.Size.offsetX / 2;
                break;
            case AnchorX::RIGHT:
                this->_filledTransform.Pos.x -= this->transform.Size.x * (1 - filled);
                this->_filledTransform.Pos.offsetX -= this->transform.Size.offsetX * (1 - filled);
                this->_handleTransform.Pos.x -= this->transform.Size.x - this->_handleTransform.Size.x;
                this->_handleTransform.Pos.offsetX -= this->transform.Size.offsetX - this->_handleTransform.Size.offsetX / 2;
                break;
        }
        switch (this->transform.AnchY) {
            case AnchorY::TOP:
                this->_handleTransform.Pos.y -= this->_handleTransform.Size.x * (static_cast<float>(this->_windowSize.first) / this->_windowSize.second) - this->transform.Size.y / 2;
                this->_handleTransform.Pos.offsetY -= this->_handleTransform.Size.offsetX - this->transform.Size.offsetY / 2;
                break;
            case AnchorY::MID:
                break;
            case AnchorY::BOTTOM:
                this->_handleTransform.Pos.y += this->_handleTransform.Size.x * (static_cast<float>(this->_windowSize.first) / this->_windowSize.second) - this->transform.Size.y / 2;
                this->_handleTransform.Pos.offsetY += this->_handleTransform.Size.offsetX;
                break;
        }
    }

    public:
        Slider(T value, T min, T max, T step, Transform transform, Options options)
            : AElement(transform, options), _filledTransform(transform), _handleTransform(transform), _value(value), _min(min), _max(max), _step(step)
        {
            if (this->_value < this->_min)
                this->_value = this->_min;
            if (this->_value > this->_max)
                this->_value = this->_max;

            this->_filledOptions.primaryColor = Color(39, 183, 245, 255);
            this->_filledOptions.outlineThickness = 0;

            this->_handleOptions.primaryColor = Color(240, 240, 240, 255);
            this->_handleOptions.secondaryColor = Color(200, 200, 200, 255);
            this->_handleOptions.outlineThickness = 2;
        }
        ~Slider() = default;

        bool handleEvent(Event event) override
        {
            if (event.type == Event::Type::MouseButtonPressed && event.mouseButton == Event::MouseButton::Left) {
                float handleX = this->_windowSize.first * this->_handleTransform.Pos.x + this->_handleTransform.Pos.offsetX + -(static_cast<float>(this->_handleTransform.AnchX) - 1) * (this->_windowSize.first * this->_handleTransform.Size.x + this->_handleTransform.Size.offsetX) + static_cast<float>(this->_handleTransform.AnchX) / 2 * this->_windowSize.first;
                float handleY = this->_windowSize.second * this->_handleTransform.Pos.y + this->_handleTransform.Pos.offsetY + -(static_cast<float>(this->_handleTransform.AnchY) - 1) * (this->_windowSize.first * this->_handleTransform.Size.x + this->_handleTransform.Size.offsetX) + static_cast<float>(this->_handleTransform.AnchY) / 2 * this->_windowSize.second;
                float radius = this->_windowSize.first * this->_handleTransform.Size.x + this->_handleTransform.Size.offsetX + this->_handleOptions.outlineThickness;
                if (std::sqrt(std::pow(event.mouseX - handleX, 2) + std::pow(event.mouseY - handleY, 2)) <= radius) {
                    this->_holding = true;
                    this->_prevMousePos = {event.mouseX, event.mouseY};
                    this->_handleOptions.primaryColor = Color(200, 200, 200, 255);
                    return true;
                }
                return false;
            }
            if (event.type == Event::Type::MouseButtonReleased && event.mouseButton == Event::MouseButton::Left && this->_holding) {
                this->_handleOptions.primaryColor = Color(240, 240, 240, 255);
                this->_holding = false;
                return true;
            }
            if (event.type == Event::Type::MouseMoved && this->_holding) {
                
            }
            return false;
        }

        void update(float deltaTime) override {(void) deltaTime;}
        void draw(IGraphic& graphicalLib) override
        {
            float filled = static_cast<float>(this->_value - this->_min) / (this->_max - this->_min);

            this->_windowSize = graphicalLib.getWindowSize();
            this->_updateTransforms(filled);

            graphicalLib.drawRectangle(this->transform, this->_options);
            graphicalLib.drawRectangle(this->_filledTransform, this->_filledOptions);
            graphicalLib.drawCircle(this->_handleTransform, this->_handleOptions);
        }
};

}

#endif /* SLIDER_HPP_ */
