/**
 * @file Image.cpp
 * @brief image clas implementation
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Image.hpp"
#include <memory>

Layout::Image::Image(Transform transform, std::string path, Options options)
    : AElement(transform, options), _path(path)
{}

void Layout::Image::update(float deltaTime)
{
    (void)deltaTime;
}

void Layout::Image::draw(Layout::IGraphic& graphicalLib)
{
    graphicalLib.drawImage(this->transform, this->_path, this->_options);
}
