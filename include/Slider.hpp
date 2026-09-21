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
    #include <iostream>

namespace Layout {

template <typename T>
class Slider : public AElement {
    T _value;
    T _min;
    T _max;
    T _step;

    public:
        Slider(T value, T min, T max, T step, Transform transform, Options options) : AElement(transform, options), _value(value), _min(min), _max(max), _step(step)
        {
            if (this->_value < this->_min)
                this->_value = this->_min;
            if (this->_value > this->_max)
                this->_value = this->_max;
        }
        ~Slider() = default;

        void update(float deltaTime) override {(void) deltaTime;}
        void draw(IGraphic& graphicalLib)
        {
            float filled = static_cast<float>(this->_value - this->_min) / (this->_max - this->_min);
            Transform filledTransform = this->transform;
            Transform handleTransform = this->transform;
            Options filledOptions = this->_options;
            auto windowSize = graphicalLib.getWindowSize();

            filledTransform.Size.x = this->transform.Size.x * filled;
            filledTransform.Size.offsetX = this->transform.Size.offsetX * filled;
            filledOptions.primaryColor = Color(39, 183, 245, 255);
            filledOptions.outlineThickness = 0;

            Options handleOptions;
            handleTransform.Size.x = this->transform.Size.y * 0.75 * (static_cast<float>(windowSize.second) / windowSize.first);
            handleTransform.Size.offsetX = this->transform.Size.offsetY * 0.75 * (static_cast<float>(windowSize.second) / windowSize.first);
            handleTransform.Size.y = handleTransform.Size.x;
            handleTransform.Size.offsetY = handleTransform.Size.offsetX;
            handleOptions.primaryColor = Color(240, 240, 240, 255);
            handleOptions.secondaryColor = Color(200, 200, 200, 255);
            handleOptions.outlineThickness = 2;

            handleTransform.Pos.x += this->transform.Size.x * filled;
            handleTransform.Pos.offsetX += this->transform.Size.offsetX * filled;

            switch (this->transform.AnchX) {
                case AnchorX::LEFT:
                    handleTransform.Pos.x -= handleTransform.Size.x;
                    handleTransform.Pos.offsetX -= handleTransform.Size.offsetX;
                    break;
                case AnchorX::MID: 
                    filledTransform.Pos.x -= this->transform.Size.x * (1 - filled) / 2;
                    filledTransform.Pos.offsetX -= this->transform.Size.offsetY * (1 - filled) / 2;
                    handleTransform.Pos.x -= this->transform.Size.x / 2;
                    handleTransform.Pos.offsetX -= this->transform.Size.offsetX / 2;
                    break;
                case AnchorX::RIGHT:
                    filledTransform.Pos.x -= this->transform.Size.x * (1 - filled);
                    filledTransform.Pos.offsetX -= this->transform.Size.offsetX * (1 - filled);
                    handleTransform.Pos.x -= this->transform.Size.x - handleTransform.Size.x;
                    handleTransform.Pos.offsetX -= this->transform.Size.offsetX - handleTransform.Size.offsetX / 2;
                    break;
            }
            switch (this->transform.AnchY) {
                case AnchorY::TOP:
                    handleTransform.Pos.y -= handleTransform.Size.x * (static_cast<float>(windowSize.first) / windowSize.second) - this->transform.Size.y / 2;
                    handleTransform.Pos.offsetY -= handleTransform.Size.offsetX - this->transform.Size.offsetY / 2;
                    break;
                case AnchorY::MID:
                    break;
                case AnchorY::BOTTOM:
                    handleTransform.Pos.y += handleTransform.Size.x * (static_cast<float>(windowSize.first) / windowSize.second) - this->transform.Size.y / 2;
                    handleTransform.Pos.offsetY += handleTransform.Size.offsetX;
                    break;
            }

            graphicalLib.drawRectangle(this->transform, this->_options);
            graphicalLib.drawRectangle(filledTransform, filledOptions);
            graphicalLib.drawCircle(handleTransform, handleOptions);
        }
};

}

#endif /* SLIDER_HPP_ */
