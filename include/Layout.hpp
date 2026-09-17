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
    std::optional<Section*> _selected;
    // std::unordered_map<std::string, fonction> _shortcuts; // TODO: shortcuts
    LibName _graphicalLib = LibName::SFML;
    int _width;
    int _height;
    // TODO: dynamic lib

    public:
        Layout() = default;
        Layout(LibName name) : _graphicalLib(name) {}

        void save(std::filesystem::path fp);
        void load(std::filesystem::path fp);

        void handleEvent(); // TODO: add event struct as param
        void update();
        void draw();

        std::vector<std::string> getData(std::string secId, std::vector<std::string> elemsId);

        void addElem(IElement element, std::string elemId, std::string secId);
        void popElem(std::string elemId, std::string secId);

        class LayoutException : public std::exception {
            protected:
                std::string _msg;
            public:
                LayoutException(std::string msg) : _msg(msg) {}

                virtual const char* what() const noexcept { return this->_msg.c_str(); }
        };

        class InvalidConfigException : public LayoutException {
            public:
                InvalidConfigException() : LayoutException("Invalid configuration file") {}
        };

};

}

#endif /* LAYOUT_HPP_ */
