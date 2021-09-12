//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_ENEMY_HPP
#define DINO_ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "texture_cycler.hpp"

class Enemy {

    sf::Sprite sprite;

public:

    Enemy(TextureCycler cycler, float scale, sf::Vector2f position);
    void move(sf::Vector2f delta);

    class Factory {

        TextureCycler cactus;
        TextureCycler bird;
        const float scale;
        const std::pair<uint, uint> yRange;
        const uint windowWidth;

    public:
        Factory(TextureCycler cactus, TextureCycler bird, float scale, decltype(yRange) yRange, uint winWidth);

        Enemy create();
    };

};

#endif //DINO_ENEMY_HPP
