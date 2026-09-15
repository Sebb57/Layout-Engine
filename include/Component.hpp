/**
 * @file Component.hpp
 * @brief component structure
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <cstdint>

namespace Layout {

enum class LibName {
    SFML
};

enum class AnchorPoints {
    LEFT,
    MID,
    RIGHT
};

struct Rect {
    float x;
    float y;
    uint32_t offsetX;
    uint32_t offsetY;
};

struct Transform {
    AnchorPoints AnchX;
    AnchorPoints AnchY;
    Rect Pos;
    Rect Size;
};

struct Event {
    enum class Type {
        None,
        Closed,
        KeyPressed,
        KeyReleased,
        TextEntered,
        MouseWheelScrolled,
        MouseMoved,
        MouseButtonPressed
    };

    enum class Key {
        Unknown,
        Escape,
        Space,
        Shift,
        Control,
        Alt,
        Left,
        Right,
        Up,
        Down,
        Delete,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
    };

    enum class MouseButton {
        None,
        Left,
        Right,
        Middle
    };

    Type type = Type::None;
    Key key = Key::Unknown;
    char keyChar = '\0';
    MouseButton mouseButton = MouseButton::None;
    double wheelDelta = 0.0;
    int mouseX = 0;
    int mouseY = 0;
};

}

#endif /* COMPONENT_HPP_ */
