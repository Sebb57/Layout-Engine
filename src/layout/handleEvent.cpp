/**
 * @file handleEvent.cpp
 * @brief method for handling events
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"
#include <iostream>
#include <string>

bool Layout::Layout::handleEvent(Event& event)
{
    if (this->_events.empty())
        return false;
    event = this->_events.back();
    this->_events.pop_back();

    if (event.type == Event::Type::KeyPressed) {
        if (this->_heldKeys.contains(event.key)) {
            event = Event{};
            return true;
        }
        this->_heldKeys.insert(event.key);

        auto it = this->_shortcuts.find(event.key);
        if (it != this->_shortcuts.end()) {
            this->openSection(it->second);
            event = Event{};
            return true;
        }
    }
    else if (event.type == Event::Type::KeyReleased) {
        this->_heldKeys.erase(event.key);
    }

    return false;
}
