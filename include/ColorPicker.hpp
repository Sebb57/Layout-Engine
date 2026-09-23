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
    Transform _darknessTransform;
    Transform _alphaTransform;
    Transform _rTransform;
    Transform _gTransform;
    Transform _bTransform;

    Slider<float> _darkness;
    Slider<float> _alpha;
    InputBox _r;
    InputBox _g;
    InputBox _b;

    void _updateTransforms() //TODO: update each transform based on the anchor point so that is match
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
        this->_darkness.transform = this->_darknessTransform;
        this->_alpha.transform = this->_alphaTransform;
        this->_r.transform = this->_rTransform;
        this->_g.transform = this->_gTransform;
        this->_b.transform = this->_bTransform;
    }

    public:
        ColorPicker(Transform transform, Options options) : AElement(transform, options),
            _darknessTransform(
                transform.AnchX,
                transform.AnchY,
                Rect(this->transform.Pos.x, this->transform.Pos.y + this->transform.Size.y, this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                Rect(this->transform.Size.x * 0.90F, this->transform.Size.y / 10.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
            ),
            _alphaTransform(
                transform.AnchX,
                transform.AnchY,
                Rect(this->transform.Pos.x, this->transform.Pos.y + (this->transform.Size.y / 0.75F), this->transform.Pos.offsetX, this->transform.Pos.offsetY),
                Rect(this->transform.Size.x * 0.90F, this->transform.Size.y / 10.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
            ),
            _rTransform(
                transform.AnchX,
                transform.AnchY,
                Rect(this->transform.Pos.x - (this->transform.Size.x * 0.135F), this->transform.Pos.y + (this->transform.Size.y / 1.75F), this->transform.Pos.offsetX - (this->transform.Size.offsetX * 0.135F), this->transform.Pos.offsetY),
                Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
            ),
            _gTransform(
                transform.AnchX,
                transform.AnchY,
                Rect(this->transform.Pos.x + (this->transform.Size.x * 0.115F), this->transform.Pos.y + (this->transform.Size.y / 1.75F), this->transform.Pos.offsetX + (this->transform.Size.offsetX * 0.115F), this->transform.Pos.offsetY),
                Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
            ),
            _bTransform(
                transform.AnchX,
                transform.AnchY,
                Rect(this->transform.Pos.x + (this->transform.Size.x * 0.365F), this->transform.Pos.y + (this->transform.Size.y / 1.75F), this->transform.Pos.offsetX + (this->transform.Size.offsetX * 0.365F), this->transform.Pos.offsetY),
                Rect(this->transform.Size.x * 0.23F, this->transform.Size.y / 4.0F, this->transform.Size.offsetX, this->transform.Size.offsetY)
            ),
            _darkness(0.0F, 0.0F, 100.0F, 0.1F, Transform(), options),
            _alpha(255.0F, 0.0F, 255.0F, 0.1F, Transform(), options),
            _r("RRR.R", Transform(), options),
            _g("GGG.G", Transform(), options),
            _b("BBB.B", Transform(), options)
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
