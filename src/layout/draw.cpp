/**
 * @file draw.cpp
 * @brief layout draw function
 *
 * @author Seb
 * @date 2026-09-17
**/

#include "AGraphic.hpp"
#include "Layout.hpp"
#include "SFML.hpp"
#include <memory>

namespace {

//TODO: make this the layout constructor
std::unique_ptr<Layout::IGraphic> graphicalFactory(Layout::LibName name, Layout::Layout& layout)
{
    switch (name) {
        case Layout::LibName::SFML :
            return std::make_unique<Layout::SFML>(layout);
        default:
            return nullptr;
    }
}

}

//TODO: fix segfault
void Layout::Layout::draw()
{
    //TODO: add graphicalLib to layout class
    static std::unique_ptr<IGraphic> graphicalLib = graphicalFactory(this->_graphicalLib, *this);
    if (!graphicalLib)
        return;

    if (!graphicalLib->isOpen())
        graphicalLib->open(this->_width, this->_height, "Layout Engine");

    graphicalLib->clear();
    for (auto& section : this->_sections) {
        //TODO: make section inherit from IElement
        graphicalLib->drawRectangle(section.second->transform);

        for (auto& element : section.second->getElementsMap() ) {
            element.second->draw(graphicalLib);
        }
    }
    graphicalLib->update();
}
