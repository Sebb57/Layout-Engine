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
#include <filesystem>
#include <string>

namespace Layout {

class Image : public AElement {
    std::filesystem::path _path;

    public:
        Image(Color fillColor, Color borderColor, std::string path) : AElement(fillColor, borderColor), _path(path) {}
        ~Image() = default;

        void update(float deltaTime) override;
        void draw() override;
};

}

#endif /* IMAGE_HPP_ */

