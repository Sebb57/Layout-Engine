/**
 * @file update.cpp
 * @brief update method for layout
 *
 * @author Seb
 * @date 2026-09-18
**/

#include "Layout.hpp"
#include <queue>

void Layout::Layout::update()
{
    std::queue<Event> events = this->_graphicalLib->listen();

    while (!events.empty()) {
        this->_events.push_back(events.front());
        events.pop();
    }
}
