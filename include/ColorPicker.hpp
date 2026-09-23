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

    void _updateTransforms()
    {
        switch (this->transform.AnchX) {
            case AnchorX::LEFT:
                break;
            case AnchorX::MID: 
                break;
            case AnchorX::RIGHT:
                break;
        }
        switch (this->transform.AnchY) {
            case AnchorY::TOP:
                break;
            case AnchorY::MID:
                break;
            case AnchorY::BOTTOM:
                break;
        }
    }

    public:
        ColorPicker(Transform transform, Options options) : AElement(transform, options),
            _darkness(
                0.0F, 0.0F, 100.0F, 0.1F,
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x, this->transform.Pos.y + this->transform.Size.y, this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.90F, this->transform.Size.y / 10.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _alpha(
                255.0F, 0.0F, 255.0F, 0.1F,
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x, this->transform.Pos.y + (this->transform.Size.y / 0.75F), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.90F, this->transform.Size.y / 10.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _r(
                "RRR.R",
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x - (this->transform.Size.x * 0.135F), this->transform.Pos.y + (this->transform.Size.y / 1.75F), this->transform.Pos.offsetX - (this->transform.Size.offsetX * 0.135F), this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _g(
                "GGG.G",
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x + (this->transform.Size.x * 0.115F), this->transform.Pos.y + (this->transform.Size.y / 1.75F), this->transform.Pos.offsetX + (this->transform.Size.offsetX * 0.115F), this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _b(
                "BBB.B",
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x + (this->transform.Size.x * 0.365F), this->transform.Pos.y + (this->transform.Size.y / 1.75F), this->transform.Pos.offsetX + (this->transform.Size.offsetX * 0.365F), this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
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
            this->_updateTransforms();

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
