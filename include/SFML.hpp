/**
 * @file SFML.hpp
 * @brief SFML Header
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#pragma once
#ifndef SFML_HPP_
    #define SFML_HPP_

    #include "AGraphic.hpp"
    #include "Component.hpp"
    #include <chrono>
    #include <filesystem>
    #include <map>
    #include <memory>
    #include <queue>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <SFML/Window.hpp>

namespace Layout {
    class SFML : public AGraphic {
        std::chrono::steady_clock::time_point _nextFrameTime = std::chrono::steady_clock::now();
        std::unique_ptr<sf::RenderWindow> _window;

        public:
            SFML(Layout& layout) noexcept : AGraphic(layout) {}
            ~SFML() override = default;

            void open(const std::size_t width, const std::size_t height, std::string title) final;
            void close() final;
            std::queue<Event> listen() const final;
            void clear() const final;
            void update() final;

            void drawRectangle(Transform transform) const final;
            void drawImage(Transform transform, std::filesystem::path path) const final;
            void drawText(Transform transform, std::string text, std::filesystem::path font) const final;
    };
}

#endif /* SFML_HPP_ */
