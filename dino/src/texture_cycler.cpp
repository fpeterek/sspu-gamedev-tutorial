//
// Created by fpeterek on 11.09.21.
//

#include "texture_cycler.hpp"

#include <cmath>

TextureCycler::TextureCycler(const std::vector<sf::Texture> & textures, const float period) :
    textures(textures), period(period), textureLifetime(period/textures.size()) { }

const sf::Texture & TextureCycler::current() {
    return textures.get()[size_t(t / textureLifetime)];
}

void TextureCycler::update(float dt) {
    t = std::fmod(t+dt, period);
}

TextureCycler::TextureCycler(TextureCycler && rv) noexcept :
    textures(rv.textures), period(rv.period), textureLifetime(rv.textureLifetime), t(rv.t) { }

TextureCycler::TextureCycler(const TextureCycler & other) :
    textures(other.textures), period(other.period), textureLifetime(other.textureLifetime) { }

TextureCycler & TextureCycler::operator=(TextureCycler && rv) noexcept {
    textures = rv.textures;
    period = rv.period;
    textureLifetime = rv.textureLifetime;
    t = rv.t;
    return *this;
}
