/**
 * @file Layout.cpp
 * @brief layout load logic
 *
 * @author Seb
 * @date 2026-09-15
**/

#include "Layout.hpp"
#include "constants.hpp"
#include <filesystem>
#include <libconfig.h++>
#include <memory>

namespace {

Layout::AnchorX resolveAnchorX(std::string anch)
{
    if (anch == "left") {
        return Layout::AnchorX::LEFT;
    } else if (anch == "middle") {
        return Layout::AnchorX::MID;
    } else {
        return Layout::AnchorX::RIGHT;
    }
}

Layout::AnchorY resolveAnchorY(std::string anch)
{
    if (anch == "top") {
        return Layout::AnchorY::TOP;
    } else if (anch == "middle") {
        return Layout::AnchorY::MID;
    } else {
        return Layout::AnchorY::BOTTOM;
    }
}

std::unique_ptr<Layout::Section> parseSection(const libconfig::Setting& sectionSetting, std::string name)
{
    Layout::Section newSection(name, true);

    newSection.transform.AnchX = resolveAnchorX(sectionSetting.lookup("anchX"));
    newSection.transform.AnchY = resolveAnchorY(sectionSetting.lookup("anchY"));
    float x, y;
    uint32_t oX, oY;
    const libconfig::Setting& pos = sectionSetting.lookup("pos");
    pos.lookupValue("x", x);
    pos.lookupValue("y", y);
    pos.lookupValue("offsetX", oX);
    pos.lookupValue("offsetY", oY);
    newSection.transform.Pos = Layout::Rect(x, y, oX, oY);

    const libconfig::Setting& size = sectionSetting.lookup("size");
    size.lookupValue("x", x);
    size.lookupValue("y", y);
    newSection.transform.Pos = Layout::Rect(x, y, 0, 0);
    return nullptr;
}

}

void Layout::Layout::load(std::filesystem::path fp)
{
    if (!std::filesystem::exists(fp) || fp.extension() != constants::ValidExtention)
        return;

    libconfig::Config cfg;
    cfg.readFile(fp);

    if (!cfg.exists("layout")) {
        throw Layout::InvalidConfigException();
    }
    const libconfig::Setting& layout = cfg.lookup("layout");
    layout.lookupValue("width", this->_width);
    layout.lookupValue("height", this->_height);

    if (!layout.lookup("sections")) {
        throw Layout::InvalidConfigException();
    }
    bool mainFound = false;
    const libconfig::Setting& sections = layout.lookup("sections");
    for (int i = 0; i < sections.getLength(); ++i) {
        const libconfig::Setting& section = sections[i];
        std::string category = section.getName();

        if (category == constants::mainWindowName) {
            mainFound = true;
        }
        this->_sections[category] = parseSection(section, category);
    }

    if (!mainFound) {
        throw Layout::InvalidConfigException();
    }
}
