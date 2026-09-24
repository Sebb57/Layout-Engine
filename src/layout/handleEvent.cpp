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

bool Layout::Layout::handleEvents()
{
    std::queue<Event> events = this->_graphicalLib->listen();

    while (!events.empty()) {
        this->_events.push_back(events.front());
        events.pop();
    }

    for (auto event: this->_events) {
        this->handleEvent(event);
        if (event.type == Event::Type::Closed) {
            this->close();
            return true;
        }
    }
    return false;
}

bool Layout::Layout::handleEvent(Event& event)
{
    if (this->_events.empty())
        return false;
    event = this->_events.back();
    this->_events.pop_back();

    if (event.type == Event::Type::MouseButtonPressed || event.type == Event::Type::MouseButtonReleased
        || event.type == Event::Type::MouseMoved || event.type == Event::Type::MouseWheelScrolled)
        for (auto & [key, section]: this->_sections)
            if (section->handleEvent(event))
                return true;

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

    if (event.type != Event::Type::MouseButtonPressed && event.type != Event::Type::MouseButtonReleased
        && event.type != Event::Type::MouseMoved && event.type != Event::Type::MouseWheelScrolled)
        for (auto & [key, section]: this->_sections)
            if (section->handleEvent(event))
                return true;

    return false;
}
