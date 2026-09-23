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
    Slider<float> _darkness;
    Slider<float> _alpha;
    InputBox _r;
    InputBox _g;
    InputBox _b;

    public:
        ColorPicker(Transform transform, Options options) : AElement(transform, options),
            _darkness(
                0.0F, 0.0F, 100.0F, 0.1F,
                Transform(
                    AnchorX::MID,
                    AnchorY::TOP,
                    Rect(transform.Pos.x, transform.Pos.y + transform.Size.y, transform.Pos.offsetX, transform.Pos.offsetY),
                    Rect(transform.Size.x * 0.90F, transform.Size.y / 10.0F, transform.Size.offsetX, transform.Size.offsetY)
                ),
                options
            ),
            _alpha(
                255.0F, 0.0F, 255.0F, 0.1F,
                Transform(
                    AnchorX::MID,
                    AnchorY::TOP,
                    Rect(transform.Pos.x, transform.Pos.y + (transform.Size.y / 0.75F), transform.Pos.offsetX, transform.Pos.offsetY),
                    Rect(transform.Size.x * 0.90F, transform.Size.y / 10.0F, transform.Size.offsetX, transform.Size.offsetY)
                ),
                options
            ),
            _r(
                "RRR.R",
                Transform(
                    AnchorX::MID,
                    AnchorY::TOP,
                    Rect(transform.Pos.x - (transform.Size.x * 0.135F), transform.Pos.y + (transform.Size.y / 1.75F), transform.Pos.offsetX - (transform.Size.offsetX * 0.135F), transform.Pos.offsetY),
                    Rect(transform.Size.x * 0.23F, transform.Size.y / 4.0F, transform.Size.offsetX, transform.Size.offsetY)
                ),
                options
            ),
            _g(
                "GGG.G",
                Transform(
                    AnchorX::MID,
                    AnchorY::TOP,
                    Rect(transform.Pos.x + (transform.Size.x * 0.115F), transform.Pos.y + (transform.Size.y / 1.75F), transform.Pos.offsetX + (transform.Size.offsetX * 0.115F), transform.Pos.offsetY),
                    Rect(transform.Size.x * 0.23F, transform.Size.y / 4.0F, transform.Size.offsetX, transform.Size.offsetY)
                ),
                options
            ),
            _b(
                "BBB.B",
                Transform(
                    AnchorX::MID,
                    AnchorY::TOP,
                    Rect(transform.Pos.x + (transform.Size.x * 0.365F), transform.Pos.y + (transform.Size.y / 1.75F), transform.Pos.offsetX + (transform.Size.offsetX * 0.365F), transform.Pos.offsetY),
                    Rect(transform.Size.x * 0.23F, transform.Size.y / 4.0F, transform.Size.offsetX, transform.Size.offsetY)
                ),
                options
            )
        {}

        ~ColorPicker() override = default;

        bool handleEvent(Event event) override
        {
            if (this->_darkness.handleEvent(event))
                return true;
            if (this->_alpha.handleEvent(event))
                return true;
            if (this->_r.handleEvent(event))
                return true;
            if (this->_g.handleEvent(event))
                return true;
            if (this->_b.handleEvent(event))
                return true;
            return false;
        }

        void update(float deltaTime) override
        {
            this->_darkness.update(deltaTime);
            this->_alpha.update(deltaTime);
            this->_r.update(deltaTime);
            this->_g.update(deltaTime);
            this->_b.update(deltaTime);
        }

        void draw(IGraphic& graphicalLib) final
        {
            graphicalLib.drawRectangle(this->transform, this->_options);

            this->_darkness.draw(graphicalLib);
            this->_alpha.draw(graphicalLib);
            this->_r.draw(graphicalLib);
            this->_g.draw(graphicalLib);
            this->_b.draw(graphicalLib);
        }

        [[nodiscard]] std::string getData() const noexcept final
        {
            return "";
        }
};

}

#endif /* COLORPICKER_HPP_ */
