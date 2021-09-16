//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_TEXTURE_CYCLER_HPP
#define DINO_TEXTURE_CYCLER_HPP

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

class TextureCycler {
    std::reference_wrapper<const std::vector<sf::Texture>> textures;
    float period;
    float textureLifetime;
    float t = 0;

public:
    TextureCycler(const std::vector<sf::Texture> & textures, float period);
    TextureCycler(TextureCycler && rv) noexcept;
    TextureCycler & operator=(TextureCycler && rv) noexcept;
    TextureCycler(const TextureCycler & other);
    void update(float dt);
    const sf::Texture & current();
};

#endif //DINO_TEXTURE_CYCLER_HPP
