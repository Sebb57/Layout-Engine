/**
 * @file TextBox.hpp
 * @brief Input Box Class Header
 *
 * @author SkyReox
 * @date 2026-09-22
**/

#pragma once
#ifndef TextBox_HPP_
    #define TextBox_HPP_

    #include "AElement.hpp"
    #include "Chronometer.hpp"
    #include <memory>

namespace {

inline constexpr float TEXT_SIZE_MULTIPLIER = 0.35;
inline constexpr unsigned CURSOR_SWAP = 1000;

}

namespace Layout {

class TextBox : public AElement {
    std::unique_ptr<Chronometer> _cursorChrono;
    Transform _textTransform;
    Options _textOptions;
    Transform _cursorTransform;
    Options _cursorOptions;
    std::pair<unsigned, unsigned> _windowSize;
    Color _secondaryColor;
    std::string _value;
    std::size_t _cursorOffset = 0;
    char _hiddenChar = '\0';
    bool _selected = false;
    bool _showCursor = false;
    bool _inserting = false;

    void _updateTransforms();

    public:
        TextBox(std::string value, Transform transform, Options options);
        ~TextBox() = default;

        bool handleEvent(Event event) override;
        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;
        [[nodiscard]] std::string getData() const noexcept final { return this->_value; }
};

}

#endif /* TextBox_HPP_ */
