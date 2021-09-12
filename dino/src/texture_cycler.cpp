//
// Created by fpeterek on 11.09.21.
//

#include "texture_cycler.hpp"

#include <cmath>

TextureCycler::TextureCycler(const std::vector<sf::Texture> & texColl, const float per) :
    textures(texColl), period(per) { }

const sf::Texture & TextureCycler::current() {
    return textures[size_t(period / t)];
}

void TextureCycler::update(float dt) {
    t = std::fmod(t+dt, period);
}

TextureCycler::TextureCycler(TextureCycler && rv) noexcept :
    textures(rv.textures), period(rv.period), t(rv.t) { }

TextureCycler::TextureCycler(const TextureCycler & other) :
    textures(other.textures), period(other.period) { }
