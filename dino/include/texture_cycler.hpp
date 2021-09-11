//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_TEXTURE_CYCLER_HPP
#define DINO_TEXTURE_CYCLER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class SpriteCycler {
    const std::vector<sf::Texture> & textures;
    const float period;
    float t = 0;

public:
    SpriteCycler(const std::vector<sf::Texture> & textures, float period);
    void update(float dt);
    const sf::Texture & current();
};

#endif //DINO_TEXTURE_CYCLER_HPP
