/**
 * @file Layout.hpp
 * @brief Layout class
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#pragma once
#ifndef LAYOUT_HPP_
    #define LAYOUT_HPP_

    #include "IElement.hpp"
    #include "GraphicalHooks.hpp"
    #include "Section.hpp"
    #include "Component.hpp"
    #include <filesystem>
    #include <memory>
    #include <optional>
    #include <unordered_map>
    #include <vector>

namespace Layout {

class Layout {
    std::unordered_map<std::string, std::unique_ptr<Section>> _sections;
    // std::vector<Event> _events; // TODO: uncomment this
    std::optional<Section&> _selected;
    // std::unordered_map<std::string, fonction> _shortcuts; // TODO: shortcuts
    LibName _graphicalLib = LibName::SFML;
    GraphicalHooks _graphicalHooks = GraphicalHooks(this->_graphicalLib);

    public:
        Layout() = default;
        Layout(LibName name) : _graphicalLib(name) { this->_graphicalHooks = GraphicalHooks(this->_graphicalLib); }

        void save(std::filesystem::path fp);
        void load(std::filesystem::path fp);

        void handleEvent(); // TODO: add event struct as param
        void update();
        void draw();

        std::vector<std::string> getData(std::string secId, std::vector<std::string> elemsId);

        void addElem(IElement element, std::string elemId, std::string secId);
        void popElem(std::string elemId, std::string secId);
};

}

#endif /* LAYOUT_HPP_ */
