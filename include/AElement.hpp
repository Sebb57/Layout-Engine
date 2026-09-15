/**
 * @file AElement.hpp
 * @brief abstract element class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef AELEMENT_HPP_
#define AELEMENT_HPP_

#include "IElement.hpp"

namespace Layout {

class AElement : public IElement {
    public:
        AElement(Color fillColor, Color borderColor) : _fillColor(fillColor), _borderColor(borderColor) {}
        ~AElement() override = default;

    protected:
        Color _fillColor;
        Color _borderColor;
};

}

#endif /* AELEMENT_HPP_ */

