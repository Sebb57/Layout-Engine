/**
 * @file Layout.cpp
 * @brief layout load logic
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Component.hpp"
#include "Layout.hpp"
#include "Options.hpp"
#include "constants.hpp"
#include "Rectangle.hpp"
#include "Text.hpp"
#include "Image.hpp"
#include <filesystem>
#include <libconfig.h++>
#include <memory>

namespace {

Layout::AnchorX resolveAnchorX(const libconfig::Setting& setting)
{
    std::string anch;

    if (!setting.lookupValue("anchX", anch))
        throw Layout::Layout::InvalidConfigException();

    if (anch == "left")
        return Layout::AnchorX::LEFT;
    if (anch == "middle")
        return Layout::AnchorX::MID;
    if (anch == "right")
        return Layout::AnchorX::RIGHT;

    throw Layout::Layout::InvalidConfigException();
}

Layout::AnchorY resolveAnchorY(const libconfig::Setting& setting)
{
    std::string anch;

    if (!setting.lookupValue("anchY", anch))
        throw Layout::Layout::InvalidConfigException();

    if (anch == "top")
        return Layout::AnchorY::TOP;
    if (anch == "middle")
        return Layout::AnchorY::MID;
    if (anch == "bottom")
        return Layout::AnchorY::BOTTOM;

    throw Layout::Layout::InvalidConfigException();
}

Layout::Rect parseRect(const libconfig::Setting& setting, bool offsets)
{
    double x = 0;
    double y = 0;
    uint32_t offsetX = 0;
    uint32_t offsetY = 0;

    if (!setting.lookupValue("x", x) || !setting.lookupValue("y", y))
        throw Layout::Layout::InvalidConfigException();
    if (offsets && (!setting.lookupValue("offsetX", offsetX) || !setting.lookupValue("offsetY", offsetY)))
        throw Layout::Layout::InvalidConfigException();

    return Layout::Rect(x, y, offsetX, offsetY);
}

Layout::Color parseColor(const libconfig::Setting& setting)
{
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;

    if (!setting.lookupValue("r", r) || !setting.lookupValue("g", g) ||
        !setting.lookupValue("b", b) || !setting.lookupValue("a", a))
        throw Layout::Layout::InvalidConfigException();

    if (r < 0 || r > 255 || g < 0 || g > 255 ||
        b < 0 || b > 255 || a < 0 || a > 255)
        throw Layout::Layout::InvalidConfigException();

    return Layout::Color(r, g, b, a);
}

std::unique_ptr<Layout::IElement> parseRectangle(const libconfig::Setting& setting, Layout::Transform transform)
{
    if (!setting.exists("fillColor") || !setting.exists("borderColor") || !setting.exists("ZIndex"))
        throw Layout::Layout::InvalidConfigException();

    const libconfig::Setting& fillColorSetting = setting.lookup("fillColor");
    const libconfig::Setting& borderColorSetting = setting.lookup("borderColor");
    int ZIndex;
    if (!fillColorSetting.isGroup() || !borderColorSetting.isGroup() || !setting.lookupValue("ZIndex", ZIndex))
        throw Layout::Layout::InvalidConfigException();

    Layout::Color borderColor = parseColor(borderColorSetting);
    Layout::Color fillColor = parseColor(fillColorSetting);
    Layout::Options options;
    options.primaryColor = fillColor;
    options.secondaryColor = borderColor;
    options.zIndex = ZIndex;

    return std::make_unique<Layout::Rectangle>(transform, options);
}

std::unique_ptr<Layout::IElement> parseText(const libconfig::Setting& setting, Layout::Transform transform)
{
    if (!setting.exists("fillColor") || !setting.exists("borderColor") || !setting.exists("textColor") || !setting.exists("content") || !setting.exists("ZIndex"))
        throw Layout::Layout::InvalidConfigException();

    std::string content;
    const libconfig::Setting& borderColorSetting = setting.lookup("borderColor");
    const libconfig::Setting& textColorSetting = setting.lookup("textColor");
    int ZIndex;
    if (!borderColorSetting.isGroup() || !textColorSetting.isGroup() || !setting.lookupValue("content", content) || !setting.lookupValue("ZIndex", ZIndex))
        throw Layout::Layout::InvalidConfigException();

    Layout::Color borderColor = parseColor(borderColorSetting);
    Layout::Color textColor = parseColor(textColorSetting);

    Layout::Options options;
    options.primaryColor = textColor;
    options.secondaryColor = borderColor;
    options.zIndex = ZIndex;

    return std::make_unique<Layout::Text>(content, transform, options);
}

std::unique_ptr<Layout::IElement> parseImage(const libconfig::Setting& setting, Layout::Transform transform)
{
    if (!setting.exists("fillColor") || !setting.exists("borderColor") || !setting.exists("path") || !setting.exists("ZIndex"))
        throw Layout::Layout::InvalidConfigException();

    std::string path;
    const libconfig::Setting& fillColorSetting = setting.lookup("fillColor");
    const libconfig::Setting& borderColorSetting = setting.lookup("borderColor");
    int ZIndex;
    if (!fillColorSetting.isGroup() || !borderColorSetting.isGroup() || !setting.lookupValue("path", path) || !setting.lookupValue("ZIndex", ZIndex))
        throw Layout::Layout::InvalidConfigException();

    Layout::Color borderColor = parseColor(borderColorSetting);
    Layout::Color fillColor = parseColor(fillColorSetting);
    Layout::Options options;
    options.primaryColor = fillColor;
    options.secondaryColor = borderColor;
    options.zIndex = ZIndex;

    return std::make_unique<Layout::Image>(transform, path, options);

}

Layout::Transform parseTransform(const libconfig::Setting& setting)
{
    if (!setting.exists("pos") || !setting.exists("size"))
        throw Layout::Layout::InvalidConfigException();

    const libconfig::Setting& pos = setting.lookup("pos");
    const libconfig::Setting& size = setting.lookup("size");
    if (!pos.isGroup() || !size.isGroup())
        throw Layout::Layout::InvalidConfigException();

    Layout::Transform newTransform;
    newTransform.AnchX = resolveAnchorX(setting);
    newTransform.AnchY = resolveAnchorY(setting);
    newTransform.Pos = parseRect(pos, true);
    newTransform.Size = parseRect(size, false);

    return newTransform;
}

std::unique_ptr<Layout::IElement> parseElement(const libconfig::Setting& setting)
{
    std::string type;

    if (!setting.lookupValue("type", type))
        throw Layout::Layout::InvalidConfigException();
    Layout::Transform transform = parseTransform(setting);

    if (type == "rectangle")
        return parseRectangle(setting, transform);
    if (type == "text")
        return parseText(setting, transform);
    if (type == "image")
        return parseImage(setting, transform);

    throw Layout::Layout::InvalidConfigException();
}

std::unique_ptr<Layout::Section> parseSection(const libconfig::Setting& setting, const std::string& name)
{
    const libconfig::Setting& fillColorSetting = setting.lookup("fillColor");
    const libconfig::Setting& borderColorSetting = setting.lookup("borderColor");
    if (!fillColorSetting.isGroup() || !borderColorSetting.isGroup())
        throw Layout::Layout::InvalidConfigException();
    Layout::Color borderColor = parseColor(borderColorSetting);
    Layout::Color fillColor = parseColor(fillColorSetting);

    Layout::Transform transform = parseTransform(setting);
    Layout::Options options;
    options.primaryColor = fillColor;
    options.secondaryColor = borderColor;
    options.zIndex = -1;

    auto newSection = std::make_unique<Layout::Section>(transform, name, true, options);

    if (!setting.exists("elements"))
        throw Layout::Layout::InvalidConfigException();
    const libconfig::Setting& elements = setting.lookup("elements");
    if (!elements.isGroup())
        throw Layout::Layout::InvalidConfigException();

    for (int i = 0; i < elements.getLength(); ++i) {
        const libconfig::Setting& elementSetting = elements[i];
        const std::string elementName = elementSetting.getName();
        if (!elementSetting.isGroup())
            throw Layout::Layout::InvalidConfigException();

        auto element = parseElement(elementSetting);
        if (!element)
            throw Layout::Layout::InvalidConfigException();
        if (!newSection->addElement(elementName, std::move(element)))
            throw Layout::Layout::InvalidConfigException();
    }
    return newSection;
}

}

void Layout::Layout::load(std::filesystem::path fp)
{
    if (!std::filesystem::exists(fp) || fp.extension() != constants::ValidExtention)
        throw Layout::Layout::InvalidConfigException();
    
    libconfig::Config cfg;
    cfg.readFile(fp.c_str());

    if (!cfg.exists("layout"))
        throw Layout::Layout::InvalidConfigException();
    const libconfig::Setting& layout = cfg.lookup("layout");

    if (!layout.lookupValue("width", this->_width) || !layout.lookupValue("height", this->_height))
        throw Layout::Layout::InvalidConfigException();
    if (this->_width <= 0 || this->_height <= 0)
        throw Layout::Layout::InvalidConfigException();

    if (!layout.exists("sections"))
        throw Layout::Layout::InvalidConfigException();
    const libconfig::Setting& sections = layout.lookup("sections");
    if (!sections.isGroup())
        throw Layout::Layout::InvalidConfigException();

    bool mainFound = false;
    for (int i = 0; i < sections.getLength(); ++i) {
        const libconfig::Setting& section = sections[i];
        const std::string category = section.getName();
        if (!section.isGroup())
            throw Layout::Layout::InvalidConfigException();

        if (category == constants::mainWindowName)
            mainFound = true;

        auto newSection = parseSection(section, category);
        if (!newSection)
            throw Layout::Layout::InvalidConfigException();
        if (this->_sections.contains(category))
            throw Layout::Layout::InvalidConfigException();
        this->_sections.emplace(category, std::move(newSection));
    }
    if (!mainFound)
        throw Layout::Layout::InvalidConfigException();
}
