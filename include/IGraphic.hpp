/**
 * @file IGraphic.hpp
 * @brief Graphical Library Interface
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#ifndef IGRAPHIC_HPP
    #define IGRAPHIC_HPP

    #include "Component.hpp"
    #include "Options.hpp"
    #include <cstddef>
    #include <cstdint>
    #include <filesystem>
    #include <memory>
    #include <queue>
    #include <vector>
    #include <string>

enum {
FILL_PADDING = 1
};

namespace Layout {

    struct RGBA {
        std::uint8_t r = 0;
        std::uint8_t g = 0;
        std::uint8_t b = 0;
        std::uint8_t a = 255;

        bool operator==(const RGBA& v) const {return this->r == v.r && this->g == v.g && this->b == v.b && this->a == v.a;}
        bool operator!=(const RGBA& v) const {return this->r != v.r || this->g != v.g || this->b != v.b || this->a != v.a;}
    };

    class IGraphic {
        public:
            virtual void open(std::size_t width = 800, std::size_t height = 600, std::string title = "LayoutEngine") = 0;
            virtual void close() = 0;
            [[nodiscard]] virtual std::queue<Event> listen() const = 0;
            virtual void clear() const = 0;
            virtual void update() = 0;
            [[nodiscard]] virtual bool isOpen() const noexcept = 0;

            virtual void drawRectangle(Transform transform, Options options) const = 0;
            virtual void drawCircle(Transform transform, Options options) const = 0;
            virtual void drawImage(Transform transform, std::filesystem::path path, Options options) const = 0;
            virtual void drawText(Transform transform, std::string text, Options options, std::filesystem::path font = "./assets/Arial Regular.ttf") const = 0;

            [[nodiscard]] virtual std::pair<unsigned, unsigned> getWindowSize() const noexcept = 0;

            IGraphic& operator=(const IGraphic& object) = delete;
            IGraphic& operator=(IGraphic&& object) = delete;

            IGraphic() = default;
            IGraphic(const IGraphic& object) = delete;
            IGraphic(IGraphic&& object) = delete;

            virtual ~IGraphic() = default;
    };

} // namespace Layout
#endif // IGRAPHIC_HPP
