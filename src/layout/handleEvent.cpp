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
    if (!this->_events.empty()) {
        event = this->_events.back();
        this->_events.pop_back();
    }

    if (this->_shortcuts.find(event.key) != this->_shortcuts.end()) {
        this->openSection(this->_shortcuts.at(event.key));
        event = Event{};
        return true;
    }
    return false;
}
