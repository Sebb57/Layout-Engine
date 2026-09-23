/**
 * @file ColorPicker.hpp
 * @brief color picker class
 *
 * @author Seb
 * @date 2026-09-22
**/

#ifndef COLORPICKER_HPP_
#define COLORPICKER_HPP_

#include "AElement.hpp"
#include "Slider.hpp"
#include "InputBox.hpp"

namespace Layout {

class ColorPicker : public AElement {
    // Slider<float> _brightness;
    // Slider<float> _alpha;
    // InputBox r;
    // InputBox g;
    // InputBox b;
    std::pair<unsigned, unsigned> _windowSize;

    public:
        ColorPicker(Transform transform, Options options) : AElement(transform, options) {} //TODO: calculate the transform of each slider and InputBox based on the ColorPicker transform
        ~ColorPicker() override = default;

        bool handleEvent(Event event) override { (void) event; return false; }
        void update(float deltaTime) override {(void) deltaTime;}
        void draw(IGraphic& graphicalLib) final
        {
            this->_windowSize = graphicalLib.getWindowSize();

            graphicalLib.drawRectangle(this->transform, this->_options);
        }

        [[nodiscard]] std::string getData() const noexcept final { return ""; }
};

}

#endif /* COLORPICKER_HPP_ */

