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
    #include "Options.hpp"
    #include <string>

namespace Layout {

class Text : public AElement {
    std::string _content;

    public:
        Text(std::string content, Transform transform, Options options);
        ~Text() = default;

        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;

        std::string getContent() { return this->_content; }
};

}

#endif /* TEXT_HPP_ */
