/**
 * @file AElement.hpp
 * @brief abstract element class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef AELEMENT_HPP_
#define AELEMENT_HPP_

#include "Component.hpp"
#include "IElement.hpp"
#include "Options.hpp"

namespace Layout {

class AElement : public IElement {
    public:
        AElement(Transform transform, Options options)
            : transform(transform), _options(options) {}
        ~AElement() override = default;
        Transform transform;

    protected:
        Options _options;
};

}

#endif /* AELEMENT_HPP_ */

