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
        const Transform& p = this->transform;
        float ax = 0.0F;
        float ay = 0.0F;

        switch (p.AnchX) {
            case AnchorX::LEFT:
                ax = 1.0F;
                break;
            case AnchorX::MID:
                ax = 0.0F;
                break;
            case AnchorX::RIGHT:
                ax = -1.0F;
                break;
        }
        switch (p.AnchY) {
            case AnchorY::TOP:
                ay = 1.0F;
                break;
            case AnchorY::MID:
                ay = 0.0F;
                break;
            case AnchorY::BOTTOM:
                ay = -1.0F;
                break;
        }

        auto place = [&](AElement& child, float dx, float dy, float sx, float sy) {
            const float fx = dx + ax * (1.0F - sx) / 2.0F;
            const float fy = dy + ay * (1.0F - sy) / 2.0F;

            child.transform.AnchX = p.AnchX;
            child.transform.AnchY = p.AnchY;

            child.transform.Pos.x = p.Pos.x + p.Size.x * fx;
            child.transform.Pos.y = p.Pos.y + p.Size.y * fy;
            child.transform.Pos.offsetX = p.Pos.offsetX + p.Size.offsetX * fx;
            child.transform.Pos.offsetY = p.Pos.offsetY + p.Size.offsetY * fy;

            child.transform.Size.x = p.Size.x * sx;
            child.transform.Size.y = p.Size.y * sy;
            child.transform.Size.offsetX = p.Size.offsetX * sx;
            child.transform.Size.offsetY = p.Size.offsetY * sy;
        };

        place(_darkness, 0.0F, 0.100F, 0.90F, 0.10F);
        place(_alpha, 0.0F, 0.375F, 0.90F, 0.10F);
        place(_r, -0.135F, -0.250F, 0.23F, 0.25F);
        place(_g, 0.115F, -0.250F, 0.23F, 0.25F);
        place(_b, 0.365F, -0.250F, 0.23F, 0.25F);
    }

    public:
        ColorPicker(Transform transform, Options options) : AElement(transform, options),
            _darkness(
                0.0F, 0.0F, 100.0F, 0.1F,
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x, this->transform.Pos.y + ((this->transform.Size.y / 2) * 0.20), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.90F, this->transform.Size.y / 10.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _alpha(
                255.0F, 0.0F, 255.0F, 0.1F,
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x, this->transform.Pos.y + ((this->transform.Size.y / 2) * 0.75), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.90F, this->transform.Size.y / 10.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _r(
                "000.0",
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x - (this->transform.Size.x * 0.135F), this->transform.Pos.y - (this->transform.Size.y * 0.25F), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _g(
                "000.0",
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x + (this->transform.Size.x * 0.115F), this->transform.Pos.y - (this->transform.Size.y * 0.25F), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            ),
            _b(
                "000.0",
                Transform(
                    transform.AnchX,
                    transform.AnchY,
                    Rect(this->transform.Pos.x + (this->transform.Size.x * 0.365F), this->transform.Pos.y - (this->transform.Size.y * 0.25F), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                    Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
                ),
                options
            )
        {
            this->_updateTransforms();
        }

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
