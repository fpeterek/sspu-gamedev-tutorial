//
// Created by fpeterek on 26.09.21.
//

#ifndef DINO_SKY_HPP
#define DINO_SKY_HPP

#include <vector>
#include <random>
#include <optional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "textures.hpp"

class Sky : public sf::Drawable {

    class Cloud : public sf::Sprite {

        float speed;

    public:

        Cloud(const sf::Texture & texture, sf::Vector2f position, float scale, float speed);
        Cloud & operator=(Cloud && other) noexcept;
        Cloud(Cloud && other) noexcept;

        float velocity() const;
    };

    static constexpr float baseCloudSpeed = -70;

    const sf::Vector2i dim;
    const float scale;
    const sf::Texture & cloudTexture;
    const size_t maxClouds;

    std::optional<std::reference_wrapper<sf::Shader>> shader;

    std::vector<Cloud> clouds;
    std::default_random_engine rand;
    std::uniform_int_distribution<int> spawnRange;
    std::uniform_real_distribution<float> cloudScale;

    void moveClouds(float dt);
    void removeClouds();
    void spawnCloud(sf::Vector2i xRange);
    void spawnCloud();
    void spawnCloudIfNecessary();

protected:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:

    Sky(sf::Vector2i dimensions, float scale, const sf::Texture & cloud, decltype(shader) shader);
    ~Sky() override = default;

    void update(float dt);
    void applyShader(sf::Shader & shader);

};

#endif //DINO_SKY_HPP
