/**
 * @file Image.hpp
 * @brief image class
 *
 * @author Seb
 * @date 2026-09-15
**/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "AElement.hpp"
#include "Options.hpp"
#include <filesystem>
#include <string>

namespace Layout {

class Image : public AElement {
    std::filesystem::path _path;

    public:
        Image(Transform transform, std::string path, Options options);
        ~Image() = default;

        void update(float deltaTime) override;
        void draw(IGraphic& graphicalLib) override;
};

}

#endif /* IMAGE_HPP_ */

