/**
 * @file handleEvent.cpp
 * @brief method for handling events
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"
#include <string>

bool Layout::Layout::handleEvent(Event& event)
{
    if (!this->_events.empty()) {
        event = this->_events.back();
        this->_events.pop_back();
    }

    std::string keyStr{event.keyChar};

    if (this->_shortcuts.find(keyStr) != this->_shortcuts.end()) {
        //TODO: call shortcut function
        event = Event{};
        return true;
    }
    return false;
}
