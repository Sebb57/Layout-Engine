/**
 * @file IGraphic.hpp
 * @brief Graphical Library Interface
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#ifndef IGRAPHIC_H
    #define IGRAPHIC_H

    #include "Component.hpp"
    #include "Options.hpp"
    #include <cstddef>
    #include <cstdint>
    #include <filesystem>
    #include <memory>
    #include <queue>
    #include <vector>
    #include <string>

    #define FILL_PADDING 1

namespace Layout {

    struct RGBA {
        std::uint8_t r = 0;
        std::uint8_t g = 0;
        std::uint8_t b = 0;
        std::uint8_t a = 255;

        bool operator==(const RGBA& v) {return this->r == v.r && this->g == v.g && this->b == v.b && this->a == v.a;}
        bool operator!=(const RGBA& v) {return this->r != v.r || this->g != v.g || this->b != v.b || this->a != v.a;}
    };

    class IGraphic {
        public:
            virtual void open(const std::size_t width = 800, const std::size_t height = 600, std::string title = "LayoutEngine") = 0;
            virtual void close() = 0;
            virtual std::queue<Event> listen() const = 0;
            virtual void clear() const = 0;
            virtual void update() = 0;
            virtual bool isOpen() const noexcept = 0;

            virtual void drawRectangle(Transform transform, Options options) const = 0;
            virtual void drawImage(Transform transform, std::filesystem::path path, Options options) const = 0;
            virtual void drawText(Transform transform, std::string text, Options options, std::filesystem::path font = "./assets/Arial Regular.ttf") const = 0;

            IGraphic& operator=(const IGraphic& object) = delete;
            IGraphic& operator=(IGraphic&& object) = delete;

            IGraphic() = default;
            IGraphic(const IGraphic& object) = delete;
            IGraphic(IGraphic&& object) = delete;

            virtual ~IGraphic() = default;
    };

}
#endif /* IGRAPHIC_H */
