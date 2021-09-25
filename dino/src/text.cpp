//
// Created by fpeterek on 19.09.21.
//

#include <text.hpp>

FontLoader * FontLoader::fl = nullptr;

const sf::Font & FontLoader::loadFont(const std::string & path, const std::string & key) {

    const std::string & realKey = (key.empty()) ? path : key;

    auto ptr = std::make_shared<sf::Font>();
    auto & font = *ptr;
    font.loadFromFile(path);
    fonts[realKey] = ptr;

    return font;
}

const sf::Font & FontLoader::get(const std::string & font) const {
    return *(fonts.at(font));
}

const sf::Font & FontLoader::operator[](const std::string & font) const {
    return get(font);
}

void FontLoader::pop(const std::string & font) {
    fonts.erase(font);
}

FontLoader & FontLoader::instance() {
    if (not fl) {
        fl = new FontLoader();
    }
    return *fl;
}

Text::Text(const sf::Font & font, const sf::Vector2f pos, const std::string & content, const uint size) {
    text.setFont(font);
    setCharacterSize(size);
    setPosition(pos);
    setString(sf::String(content));
    adjustPosition();
}

void Text::adjustPosition() {
    const float width = text.getGlobalBounds().width;
    const float height = text.getGlobalBounds().height;

    float origX = 0;

    if (alignment == Align::TopCenter or alignment == Align::Center or alignment == Align::BottomCenter) {
        origX = width / 2;
    } else if (alignment == Align::TopRight or alignment == Align::CenterRight or alignment == Align::BottomRight) {
        origX = width;
    }

    float origY = 0;

    if (alignment == Align::CenterLeft or alignment == Align::Center or alignment == Align::CenterRight) {
        origY = height / 2;
    } else if (alignment == Align::BottomLeft or alignment == Align::BottomCenter or alignment == Align::BottomRight) {
        origY = height;
    }

    text.setOrigin(origX, origY);
}

void Text::adjustSize() {
    text.setCharacterSize(size * scale);
    text.setOutlineThickness(outlineThickness * scale);
}

void Text::align(const Text::Align al) {
    alignment = al;
    adjustPosition();
}

void Text::setPosition(const sf::Vector2f position) {
    text.setPosition(position);
    adjustPosition();
}

void Text::setString(const sf::String & str) {
    text.setString(str);
    adjustPosition();
}

void Text::setCharacterSize(const uint charSize) {
    size = charSize;
    adjustSize();
    adjustPosition();
}

void Text::setScale(float newScale) {
    scale = newScale;
    adjustSize();
    adjustPosition();
}

void Text::setFillColor(const sf::Color color) {
    text.setFillColor(color);
}

void Text::setOutlineColor(const sf::Color color) {
    text.setOutlineColor(color);
}

void Text::setOutlineThickness(const float thickness) {
    outlineThickness = thickness;
    adjustSize();
}

void Text::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    if (not hidden) {
        target.draw(text, states);
    }
}

void Text::show() {
    hidden = false;
}

void Text::hide() {
    hidden = true;
}


