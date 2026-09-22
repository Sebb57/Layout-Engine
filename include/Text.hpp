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

        bool handleEvent(Event event) override { (void) event; return false; }
        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;

        [[nodiscard]] std::string getData() const noexcept final { return this->_content; }
};

}

#endif /* TEXT_HPP_ */
