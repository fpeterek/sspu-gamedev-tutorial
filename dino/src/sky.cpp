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
    for (const Cloud & cloud : clouds) {
        target.draw(cloud, states);
    }
}

Sky::Sky(const sf::Vector2i dimensions, float scale, const sf::Texture & cloud) :
    dim(dimensions), scale(scale), cloudTexture(cloud), maxClouds(dimensions.y / scale / 15),
    rand(time(nullptr)), spawnRange(0, dimensions.y * 0.8f),
    cloudScale(scale * 0.8f, scale * 1.2f) {

    const int fraction = dimensions.x / maxClouds;
    for (int i = 0; i < maxClouds; ++i) {
        spawnCloud({ i * fraction, (i+1) * fraction });
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














