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
    setFont(font);
    setCharacterSize(size);
    setPosition(pos);
    setString(sf::String(content));
    adjustPosition();
}

void Text::adjustPosition() {
    const float width = getGlobalBounds().width;
    const float height = getGlobalBounds().height;

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

    setOrigin(origX, origY);
}

void Text::align(const Text::Align al) {
    alignment = al;
    adjustPosition();
}

void Text::setPosition(const sf::Vector2f position) {
    sf::Text::setPosition(position);
    adjustPosition();
}

void Text::setString(const sf::String & str) {
    sf::Text::setString(str);
    adjustPosition();
}

void Text::setCharacterSize(const uint size) {
    sf::Text::setCharacterSize(size);
    adjustPosition();
}
