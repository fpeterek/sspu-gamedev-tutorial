//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_ENEMY_HPP
#define DINO_ENEMY_HPP

#include <random>

#include <SFML/Graphics.hpp>

#include "texture_cycler.hpp"

class Enemy {

    sf::Sprite sprite;
    TextureCycler textureCycler;
    sf::Vector2f hitboxSize;
    Enemy(TextureCycler cycler, float scale, sf::Vector2f position, sf::Vector2f hitboxSize);

public:

    sf::FloatRect hitbox() const;
    void update(float dt);
    void move(sf::Vector2f delta);

    class Factory {

        TextureCycler cactus;
        TextureCycler bird;
        const float scale;
        const std::pair<uint, uint> yRange;
        const uint windowWidth;
        std::default_random_engine rand;

        Enemy createBird();
        Enemy createCactus();

    public:
        Factory(TextureCycler cactus, TextureCycler bird, float scale, decltype(yRange) yRange, uint winWidth);

        Enemy create();
    };

};

#endif //DINO_ENEMY_HPP
