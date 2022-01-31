//
// Created by fpeterek on 26.09.21.
//

#include "sky.hpp"
#include <iostream>

#include "util.hpp"

Sky::Cloud::Cloud(const sf::Texture & texture, const sf::Vector2f position, const float scale, const float speed) :
    sf::Sprite(texture), speed(speed) {

    setScale(scale, scale);
    setPosition(position);
}

Sky::Cloud::Cloud(Sky::Cloud && other) noexcept: speed(other.speed) {
    setTexture(*other.getTexture());
    setScale(other.getScale());
    setPosition(other.getPosition());
}

Sky::Cloud & Sky::Cloud::operator=(Sky::Cloud && other) noexcept {
    speed = other.speed;
    setTexture(*other.getTexture());
    setScale(other.getScale());
    setPosition(other.getPosition());

    return *this;
}

float Sky::Cloud::velocity() const {
    return speed;
}

void Sky::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    if (skyShader.has_value()) {
        auto & sh = skyShader->get();
        states.shader = &sh;

        sh.setUniform("sunPosition", sf::Vector2f { 300.f, 700.f });
        sh.setUniform("groundLevel", 1200.f);
    }

    if (shader.has_value()) {
        auto & sh = shader->get();
        sh.setUniform("sunPosition", sf::Vector2f { 300.f, 700.f });
        sh.setUniform("groundLevel", 1200.f);
    }
    // sf::RectangleShape rect { sf::Vector2f(dim.x, dim.y) };
    // rect.setFillColor(sf::Color { 64, 198, 255 });
    if (skyShader.has_value()) {
        skyShader->get().setUniform("texture", sf::Shader::CurrentTexture);
    }
    target.draw(skySprite, states);

    for (const Cloud & cloud : clouds) {
        if (shader.has_value()) {
            states.shader = &shader->get();
            shader->get().setUniform("texture", sf::Shader::CurrentTexture);
        }
        target.draw(cloud, states);
    }
}

Sky::Sky(const sf::Vector2i dimensions, float scale, const sf::Texture & cloud, decltype(skyShader) skyShader,
         decltype(shader) shader) :
    dim(dimensions), scale(scale), cloudTexture(cloud), maxClouds(dimensions.y / scale / 15),
    skyShader(skyShader), shader(shader), rand(time(nullptr)), spawnRange(0, dimensions.y * 0.8f),
    cloudScale(scale * 0.8f, scale * 1.2f) {

    sf::Image img;
    img.create(dim.x, dim.y, { 64, 198, 255 });
    skyTexture.loadFromImage(img);
    skySprite.setTexture(skyTexture);

    const int fraction = dimensions.x / maxClouds;
    for (size_t i = 0; i < maxClouds; ++i) {
        spawnCloud({ (int)i * fraction, (int)(i+1) * fraction });
    }
}

void Sky::update(const float dt) {
    moveClouds(dt);
    removeClouds();
    spawnCloudIfNecessary();
}

void Sky::moveClouds(const float dt) {
    for (Cloud & cl : clouds) {
        cl.move(cl.velocity() * dt, 0.f);
    }
}

void Sky::removeClouds() {
    while (not clouds.empty()) {
        const auto bounds = clouds.front().getGlobalBounds();
        const auto right = bounds.left + bounds.width;
        if (right >= 0) {
            break;
        }
        clouds.erase(clouds.begin());
    }
}

void Sky::spawnCloudIfNecessary() {
    if (clouds.size() < maxClouds) {
        spawnCloud();
    }
}

void Sky::spawnCloud(sf::Vector2i xRange) {
    spawnCloud();
    const int cloudWidth = clouds.back().getGlobalBounds().width;
    std::uniform_int_distribution<uint> xrange(xRange.x, xRange.y + cloudWidth);
    clouds.back().setPosition({ (float)xrange(rand), clouds.back().getPosition().y });
}

void Sky::spawnCloud() {
    const float s = cloudScale(rand);

    const sf::Vector2f position(dim.x, spawnRange(rand));
    const float v = baseCloudSpeed * s;
    clouds.emplace_back(cloudTexture, position, s, v);
}

void Sky::applyShader(sf::Shader & sh) {
    shader.emplace(sh);
}

void Sky::applySkyShader(sf::Shader & newShader) {
    skyShader.emplace(newShader);
}














