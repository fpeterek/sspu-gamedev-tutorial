//
// Created by fpeterek on 08.09.21.
//

#include "dino.hpp"

#include <cmath>


Dino::Dino(const std::vector<sf::Texture> & textures, const float cyclePeriod) :
    textures(textures),
    sprite(textures.front()),
    cyclePeriod(cyclePeriod),
    textureLifetime(cyclePeriod / textures.size()) {

    sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
}

void Dino::setPosition(const sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Dino::setScale(const float sx, const float sy) {
    sprite.setScale(sx, sy);
}

void Dino::setScale(const sf::Vector2f scales) {
    sprite.setScale(scales);
}

void Dino::update(const float dt) {
    t += dt;
    t = std::fmod(t, cyclePeriod);
    const auto & tex = textures[size_t(t / textureLifetime)];
    sprite.setTexture(tex);
}

void Dino::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

sf::Vector2f Dino::size() const {
    return { width(), height() };
}

float Dino::width() const {
    return sprite.getTextureRect().width * sprite.getScale().x;
}

float Dino::height() const {
    return sprite.getTextureRect().height * sprite.getScale().y;
}
