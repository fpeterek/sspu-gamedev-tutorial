//
// Created by fpeterek on 09.09.21.
//

#include "texture_loader.hpp"

#include <cmath>


void TextureLoader::pop(const std::string & texture) {
    textures.erase(texture);
}

const sf::Texture & TextureLoader::load(const std::string & texture, const sf::IntRect area) {
    const auto tex = std::make_shared<sf::Texture>();
    tex->loadFromFile(texture, area);
    textures[texture] = tex;
    return *tex;
}

const sf::Texture & TextureLoader::get(const std::string & texture) const {
    return *(textures.at(texture));
}

const sf::Texture & TextureLoader::operator[](const T & texture) const {
    return get(texture.key);
}

const std::vector<sf::Texture> & TextureLoader::operator[](const S & texture) const {
    return getSheet(texture.key);
}

const std::vector<sf::Texture> & TextureLoader::getSheet(const std::string & sheet) const {
    return *(sheets.at(sheet));
}

void TextureLoader::popSheet(const std::string & sheet) {
    sheets.erase(sheet);
}

const std::vector<sf::Texture> & TextureLoader::loadSheet(
    const std::string & sheet, const sf::Vector2u texSize, const uint texCount) {

    sf::Image img;
    img.loadFromFile(sheet);
    const uint count = std::min(texCount, img.getSize().x / texSize.x);

    auto vec = std::make_shared<std::vector<sf::Texture>>();
    vec->reserve(count);

    for (size_t i = 0; i < count; ++i) {
        vec->emplace_back();
        auto & tex = vec->back();
        tex.loadFromImage(img, { int(i*texSize.x), 0, (int)texSize.x, (int)texSize.y });
    }

    sheets[sheet] = vec;
    return *vec;
}


T::T(std::string key) : key(std::move(key)) { }

S::S(std::string key) : key(std::move(key)) { }
