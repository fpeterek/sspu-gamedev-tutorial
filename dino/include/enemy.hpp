//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_ENEMY_HPP
#define DINO_ENEMY_HPP

#include <random>
#include <optional>

#include <SFML/Graphics.hpp>

#include "texture_cycler.hpp"

class Enemy : public sf::Drawable {

    sf::Sprite sprite;
    TextureCycler textureCycler;
    sf::Vector2f hitboxSize;
    Enemy(TextureCycler cycler, float scale, sf::Vector2f position, sf::Vector2f hitboxSize);

public:

    Enemy(Enemy && rvalue) noexcept;
    Enemy & operator=(Enemy && rvalue) noexcept;

    sf::FloatRect hitbox() const;
    void update(float dt);
    void move(sf::Vector2f delta);

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:

    class Factory {

        TextureCycler cactus;
        TextureCycler bird;
        const float scale;
        const std::pair<uint, uint> yRange;
        const uint windowWidth;
        const uint cactusChance;
        std::default_random_engine rand;

        Factory(
            TextureCycler cactus,
            TextureCycler bird,
            float scale,
            decltype(yRange) yRange,
            uint winWidth,
            uint cactusChance
        );

    public:


        class Builder {
            std::optional<TextureCycler> cactus;
            std::optional<TextureCycler> bird;
            float scale = 1.0;
            std::optional<decltype(yRange)> spawnRange;
            uint winWidth = sf::VideoMode::getDesktopMode().width;
            uint cactusChance = 50;

        public:

            Builder & setCactusTexture(TextureCycler cactus);
            Builder & setBirdTexture(TextureCycler bird);
            Builder & setScale(float scale);
            Builder & setSpawnRange(decltype(Factory::yRange) spawnRange);
            Builder & setWindowWidth(uint width);
            Builder & setCactusChance(uint chance);
            Builder & setBirdChance(uint chance);

            Factory create();
        };

        Enemy createBird();
        Enemy createCactus();
        Enemy create();
    };

};

#endif //DINO_ENEMY_HPP
