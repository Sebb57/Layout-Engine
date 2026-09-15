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

    public:
        Text(Color fillColor, Color borderColor, Color textColor, std::string content) : AElement(fillColor, borderColor), _content(content), _textColor(textColor) {}
        ~Text() = default;

        void update(float deltaTime) override;
        void draw() override;
};

}

#endif /* TEXT_HPP_ */

