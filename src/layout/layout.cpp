/**
 * @file layout.cpp
 * @brief layout constructor 
 *
 * @author Seb
 * @date 2026-09-17
**/

#include "Layout.hpp"
#include "Component.hpp"
#include "SFML.hpp"

Layout::Layout::Layout()
{
    this->_graphicalLib = std::make_unique<SFML>(*this);
}

Layout::Layout::Layout(LibName name) : _graphicalLibName(name)
{
    switch (name) {
        case  LibName::SFML :
            this->_graphicalLib = std::make_unique<SFML>(*this);
            break;
    }
}
