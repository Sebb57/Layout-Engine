/**
 * @file AElement.hpp
 * @brief abstract element class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef AELEMENT_HPP_
#define AELEMENT_HPP_

#include "Color.hpp"
#include "Component.hpp"
#include "IElement.hpp"

namespace Layout {

class AElement : public IElement {
    public:
        AElement(Transform transform, Color fillColor, Color borderColor, int zIndex = 0) : transform(transform), _fillColor(fillColor), _borderColor(borderColor), _zIndex(zIndex) {}
        ~AElement() override = default;
        Transform transform;

    protected:
        Color _fillColor;
        Color _borderColor;
        int _zIndex = 0;
};

}

#endif /* AELEMENT_HPP_ */

