/**
 * @file AGraphic.hpp
 * @brief Graphical Library Abstract Class
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#pragma once
#ifndef AGRAPHIC_HPP_
    #define AGRAPHIC_HPP_

#include "IGraphic.hpp"

namespace Layout {
    class Layout;

    class AGraphic : public IGraphic {
        protected:
            Layout& _layout;
            std::size_t _width = 0;
            std::size_t _height = 0;
            bool _isOpen = false;

        public:
            AGraphic(Layout& layout) : _layout(layout) {}
            ~AGraphic() override = default;

            bool isOpen() const noexcept final { return this->_isOpen; }
    };
}

#endif /* AGRAPHIC_HPP_ */
