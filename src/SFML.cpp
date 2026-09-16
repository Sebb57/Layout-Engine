/**
 * @file SFML.cpp
 * @brief SFML
 *
 * @author SkyReox
 * @date 2026-09-15
**/

#include "Component.hpp"
#include "constants.hpp"
#include "SFML.hpp"
#include <cmath>
#include <iostream>
#include <queue>
#include <thread>
#include <SFML/Graphics.hpp>

namespace {

template <typename T>
T getAnchorPoint(Layout::Transform transform, T windowSize)
{
    T res;

    switch (transform.AnchX) {
        case (Layout::AnchorX::LEFT):
            res.x = 0;
            break;
        case (Layout::AnchorX::MID):
            res.x = windowSize.x / 2;
            break;
        case (Layout::AnchorX::RIGHT):
            res.x = windowSize.x;
            break;
    }
    switch (transform.AnchY) {
        case (Layout::AnchorY::TOP):
            res.y = 0;
            break;
        case (Layout::AnchorY::MID):
            res.y = windowSize.y / 2;
            break;
        case (Layout::AnchorY::BOTTOM):
            res.y = windowSize.y;
            break;
    }
    return res;
}

inline sf::Vector2f getPosFromTransform(Layout::Rect rect, sf::Vector2u windowSize, sf::Vector2u anchorPoint)
{
    return {anchorPoint.x + windowSize.x * rect.x + rect.offsetX, anchorPoint.y + windowSize.y * rect.y + rect.offsetY};
}

inline sf::Vector2f getSizeFromTransform(Layout::Rect rect, sf::Vector2u windowSize)
{
    return {windowSize.x * rect.x + rect.offsetX, windowSize.y * rect.y + rect.offsetY};
}

// sf::Color colorNormalize(arcade::RGBA color)
// {
//     return sf::Color(color.r, color.g, color.b, color.a);
// }

}


void Layout::SFML::open(const std::size_t width, const std::size_t height, std::string title)
{
    if (this->_isOpen)
        return;
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height, 32), title, sf::Style::Default);
    this->_window->setFramerateLimit(constants::FPS_LIMIT);

    this->_width = width;
    this->_height = height;
    this->_nextFrameTime = std::chrono::steady_clock::now();

    this->_isOpen = true;
}

void Layout::SFML::close()
{
    if (!this->_isOpen)
        return;
    this->_window->close();
    this->_window.reset();
    this->_isOpen = false;
}

std::queue<Layout::Event> Layout::SFML::listen() const
{
    std::queue<Event> events;
    sf::Event sfmlEvent;

    if (!this->_isOpen || !this->_window)
        return events;
    while (this->_window->pollEvent(sfmlEvent)) {
        Event event;

        if (sfmlEvent.type == sf::Event::Closed || (sfmlEvent.type == sf::Event::KeyPressed && sfmlEvent.key.code == sf::Keyboard::Q)) {
            event.type = Event::Type::Closed;
            events.push(event);
            continue;
        }
        if (sfmlEvent.type == sf::Event::KeyPressed) {
            event.type = Event::Type::KeyPressed;
            switch (sfmlEvent.key.code) {
                case sf::Keyboard::Left:
                    event.key = Event::Key::Left;
                    break;
                case sf::Keyboard::Right:
                    event.key = Event::Key::Right;
                    break;
                case sf::Keyboard::Down:
                    event.key = Event::Key::Down;
                    break;
                case sf::Keyboard::Up:
                    event.key = Event::Key::Up;
                    break;
                case sf::Keyboard::Enter:
                    event.key = Event::Key::Enter;
                    break;
                case sf::Keyboard::Escape:
                    event.key = Event::Key::Escape;
                    break;
                case sf::Keyboard::Space:
                    event.key = Event::Key::Space;
                    break;
                case sf::Keyboard::A:
                    event.key = Event::Key::A;
                    break;
                case sf::Keyboard::B:
                    event.key = Event::Key::B;
                    break;
                case sf::Keyboard::C:
                    event.key = Event::Key::C;
                    break;
                case sf::Keyboard::D:
                    event.key = Event::Key::D;
                    break;
                case sf::Keyboard::E:
                    event.key = Event::Key::E;
                    break;
                case sf::Keyboard::F:
                    event.key = Event::Key::F;
                    break;
                case sf::Keyboard::G:
                    event.key = Event::Key::G;
                    break;
                case sf::Keyboard::H:
                    event.key = Event::Key::H;
                    break;
                case sf::Keyboard::I:
                    event.key = Event::Key::I;
                    break;
                case sf::Keyboard::J:
                    event.key = Event::Key::J;
                    break;
                case sf::Keyboard::K:
                    event.key = Event::Key::K;
                    break;
                case sf::Keyboard::L:
                    event.key = Event::Key::L;
                    break;
                case sf::Keyboard::M:
                    event.key = Event::Key::M;
                    break;
                case sf::Keyboard::N:
                    event.key = Event::Key::N;
                    break;
                case sf::Keyboard::O:
                    event.key = Event::Key::O;
                    break;
                case sf::Keyboard::P:
                    event.key = Event::Key::P;
                    break;
                case sf::Keyboard::Q:
                    event.key = Event::Key::Q;
                    break;
                case sf::Keyboard::R:
                    event.key = Event::Key::R;
                    break;
                case sf::Keyboard::S:
                    event.key = Event::Key::S;
                    break;
                case sf::Keyboard::T:
                    event.key = Event::Key::T;
                    break;
                case sf::Keyboard::U:
                    event.key = Event::Key::U;
                    break;
                case sf::Keyboard::V:
                    event.key = Event::Key::V;
                    break;
                case sf::Keyboard::W:
                    event.key = Event::Key::W;
                    break;
                case sf::Keyboard::X:
                    event.key = Event::Key::X;
                    break;
                case sf::Keyboard::Y:
                    event.key = Event::Key::Y;
                    break;
                case sf::Keyboard::Z:
                    event.key = Event::Key::Z;
                    break;
                default:
                    break;
            }
            event.keyChar = static_cast<char>(sfmlEvent.key.code);
            events.push(event);
        }
        if (sfmlEvent.type == sf::Event::KeyReleased) {
            event.type = Event::Type::KeyReleased;
            switch (sfmlEvent.key.code) {
                case sf::Keyboard::Left:
                    event.key = Event::Key::Left;
                    break;
                case sf::Keyboard::Right:
                    event.key = Event::Key::Right;
                    break;
                case sf::Keyboard::Down:
                    event.key = Event::Key::Down;
                    break;
                case sf::Keyboard::Up:
                    event.key = Event::Key::Up;
                    break;
                case sf::Keyboard::Enter:
                    event.key = Event::Key::Enter;
                    break;
                case sf::Keyboard::Escape:
                    event.key = Event::Key::Escape;
                    break;
                case sf::Keyboard::Space:
                    event.key = Event::Key::Space;
                    break;
                case sf::Keyboard::A:
                    event.key = Event::Key::A;
                    break;
                case sf::Keyboard::B:
                    event.key = Event::Key::B;
                    break;
                case sf::Keyboard::C:
                    event.key = Event::Key::C;
                    break;
                case sf::Keyboard::D:
                    event.key = Event::Key::D;
                    break;
                case sf::Keyboard::E:
                    event.key = Event::Key::E;
                    break;
                case sf::Keyboard::F:
                    event.key = Event::Key::F;
                    break;
                case sf::Keyboard::G:
                    event.key = Event::Key::G;
                    break;
                case sf::Keyboard::H:
                    event.key = Event::Key::H;
                    break;
                case sf::Keyboard::I:
                    event.key = Event::Key::I;
                    break;
                case sf::Keyboard::J:
                    event.key = Event::Key::J;
                    break;
                case sf::Keyboard::K:
                    event.key = Event::Key::K;
                    break;
                case sf::Keyboard::L:
                    event.key = Event::Key::L;
                    break;
                case sf::Keyboard::M:
                    event.key = Event::Key::M;
                    break;
                case sf::Keyboard::N:
                    event.key = Event::Key::N;
                    break;
                case sf::Keyboard::O:
                    event.key = Event::Key::O;
                    break;
                case sf::Keyboard::P:
                    event.key = Event::Key::P;
                    break;
                case sf::Keyboard::Q:
                    event.key = Event::Key::Q;
                    break;
                case sf::Keyboard::R:
                    event.key = Event::Key::R;
                    break;
                case sf::Keyboard::S:
                    event.key = Event::Key::S;
                    break;
                case sf::Keyboard::T:
                    event.key = Event::Key::T;
                    break;
                case sf::Keyboard::U:
                    event.key = Event::Key::U;
                    break;
                case sf::Keyboard::V:
                    event.key = Event::Key::V;
                    break;
                case sf::Keyboard::W:
                    event.key = Event::Key::W;
                    break;
                case sf::Keyboard::X:
                    event.key = Event::Key::X;
                    break;
                case sf::Keyboard::Y:
                    event.key = Event::Key::Y;
                    break;
                case sf::Keyboard::Z:
                    event.key = Event::Key::Z;
                    break;
                default:
                    break;
            }
            event.keyChar = static_cast<char>(sfmlEvent.key.code);
            events.push(event);
        }
    }

    return events;
}

void Layout::SFML::clear() const
{
    if (!this->_isOpen || !this->_window)
        return;
    this->_window->clear(sf::Color::Black);
}

void Layout::SFML::update()
{
    if (!this->_isOpen || !this->_window)
        return;
    std::this_thread::sleep_until(this->_nextFrameTime);
    sf::Vector2u windowSize = this->_window->getSize();
    this->_width = windowSize.x;
    this->_height = windowSize.y;
    this->_window->display();
    this->_nextFrameTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(1000 / constants::FPS_LIMIT);
}

void Layout::SFML::drawRectangle(Transform transform) const
{
    sf::RectangleShape rectangle;

    if (!this->_isOpen || !this->_window)
        return;
    sf::Vector2u windowSize = this->_window->getSize();
    sf::Vector2u anchorPoint = getAnchorPoint<sf::Vector2u>(transform, windowSize);
    rectangle.setPosition(getPosFromTransform(transform.Pos, windowSize, anchorPoint));
    rectangle.setSize(getSizeFromTransform(transform.Size, windowSize));
    rectangle.setOrigin(getAnchorPoint<sf::Vector2f>(transform, rectangle.getSize()));
    // rectangle.setRotation(angle);
    // rectangle.setOutlineColor(colorNormalize(bcolor));
    // rectangle.setOutlineThickness(1.0f);
    // if (fill)
    //     rectangle.setFillColor(colorNormalize(color));
    // else
    //     rectangle.setFillColor(sf::Color::Transparent);
    this->_window->draw(rectangle);
}

void Layout::SFML::drawImage(Transform transform, std::filesystem::path path) const
{
    sf::Texture texture;

    if (!this->_isOpen || !this->_window)
        return;
    if (!texture.loadFromFile(path))
        return;

    sf::Sprite sprite;
    sf::Vector2u windowSize = this->_window->getSize();
    sf::Vector2u anchorPoint = getAnchorPoint<sf::Vector2u>(transform, windowSize);
    sprite.setPosition(getPosFromTransform(transform.Pos, windowSize, anchorPoint));
    // sprite.setTexture(texture);
    // sprite.setPosition(normalizedOrigin);
    // sprite.setOrigin({textureSize.x / 2.0f, textureSize.y / 2.0f});
    // sprite.setRotation(angle);
    // sprite.setScale({scale, scale});

    this->_window->draw(sprite);
}

void Layout::SFML::drawText(Transform transform, std::string text, std::filesystem::path font) const
{
    sf::Font sfmlFont;

    if (!this->_isOpen || !this->_window)
        return;
    sfmlFont.loadFromFile(font);

    sf::Text sfmlText;
    sf::Vector2u windowSize = this->_window->getSize();
    sf::Vector2u anchorPoint = getAnchorPoint<sf::Vector2u>(transform, windowSize);
    sfmlText.setFont(sfmlFont);
    sfmlText.setCharacterSize(windowSize.x * transform.Size.x + transform.Size.x);
    // sfmlText.setFillColor(colorNormalize(color));
    // sfmlText.setOutlineColor(colorNormalize(fcolor));
    // sfmlText.setOutlineThickness(2 * scale);
    sfmlText.setString(text);

    sfmlText.setPosition(getPosFromTransform(transform.Pos, windowSize, anchorPoint));
    this->_window->draw(sfmlText);
}

extern "C" {
    Layout::IGraphic *factory(Layout::Layout& layout)
    {
        return new Layout::SFML(layout);
    }
}
