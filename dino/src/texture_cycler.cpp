//
// Created by fpeterek on 11.09.21.
//

#include "texture_cycler.hpp"

#include <cmath>

SpriteCycler::SpriteCycler(const std::vector<sf::Texture> & texColl, const float per) :
    textures(texColl), period(per) { }

const sf::Texture & SpriteCycler::current() {
    return textures[size_t(period / t)];
}

void SpriteCycler::update(float dt) {
    t = std::fmod(t+dt, period);
}
