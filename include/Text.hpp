/**
 * @file Text.hpp
 * @brief text class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "AElement.hpp"
#include <string>

namespace Layout {

class Text : public AElement {
    std::string _content;
    Color _textColor;
    unsigned _outlineThickness;

    public:
        Text(std::string content, Transform transform, Color textColor, unsigned outlineThickness, Color borderColor, int zIndex = 0);
        ~Text() = default;

        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;
};

}

#endif /* TEXT_HPP_ */

