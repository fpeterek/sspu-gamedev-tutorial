//
// Created by fpeterek on 11.09.21.
//

#include "enemy.hpp"

#include <cmath>
#include <utility>


Enemy::Factory::Factory(
    TextureCycler cactus, TextureCycler bird, const float scale, const decltype(yRange) yRange, const uint winWidth,
    const uint cactusChance) :
    cactus(std::move(cactus)), bird(std::move(bird)), scale(scale), yRange(yRange), windowWidth(winWidth),
    rand(time(nullptr)), cactusChance(cactusChance) { }

Enemy Enemy::Factory::create() {
    if (std::uniform_int_distribution(1, 100)(rand) > cactusChance) {
        return createBird();
    }
    return createCactus();
}

Enemy Enemy::Factory::createBird() {
    std::uniform_int_distribution dist {
        (int)yRange.first,
        (int)std::round(yRange.second - cactus.current().getSize().y*scale - bird.current().getSize().y*scale)
    };

    const float y = dist(rand);

    return {
        bird,
        scale,
        { (float)windowWidth, y },
        { 14 * scale, 6 * scale }
    };
}

Enemy Enemy::Factory::createCactus() {
    const float y = yRange.second - cactus.current().getSize().y*scale;
    return {
        cactus,
        scale,
        { (float)windowWidth, y },
        { 10 * scale, 14 * scale }
    };
}

sf::FloatRect Enemy::hitbox() const {
    return {
        sprite.getPosition().x + (sprite.getGlobalBounds().width - hitboxSize.x) / 2,
        sprite.getPosition().y + (sprite.getGlobalBounds().height - hitboxSize.y) / 2,
        hitboxSize.x,
        hitboxSize.y
    };
}

void Enemy::update(const float dt) {
    textureCycler.update(dt);
    sprite.setTexture(textureCycler.current());
}

void Enemy::move(const sf::Vector2f delta) {
    sprite.move(delta);
}

Enemy::Enemy(TextureCycler cycler, float scale, sf::Vector2f position, sf::Vector2f hitboxSize) :
    textureCycler(std::move(cycler)), hitboxSize(hitboxSize) {

    sprite.setTexture(textureCycler.current());
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
}

Enemy::Enemy(Enemy && rvalue) noexcept :
    sprite(std::move(rvalue.sprite)), textureCycler(std::move(rvalue.textureCycler)),
    hitboxSize(rvalue.hitboxSize) { }

void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

Enemy & Enemy::operator=(Enemy && other) noexcept {
    sprite = other.sprite;
    textureCycler = std::move(other.textureCycler);
    hitboxSize = other.hitboxSize;
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setCactusTexture(TextureCycler cactusTex) {
    cactus.emplace(std::move(cactusTex));
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setBirdTexture(TextureCycler birdTex) {
    bird.emplace(std::move(birdTex));
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setScale(const float sc) {
    scale = sc;
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setSpawnRange(const decltype(Factory::yRange) range) {
    spawnRange.emplace(range);
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setWindowWidth(const uint width) {
    winWidth = width;
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setCactusChance(uint chance) {
    chance = std::min(chance, 100u);
    cactusChance = chance;
    return *this;
}

Enemy::Factory::Builder & Enemy::Factory::Builder::setBirdChance(uint chance) {
    return setCactusChance(100 - std::min(chance, 100u));
}

Enemy::Factory Enemy::Factory::Builder::create() {

    if (not cactus.has_value()) {
        throw std::runtime_error("Cactus texture was not provided.");
    }
    if (not bird.has_value()) {
        throw std::runtime_error("Bird texture was not provided.");
    }
    if (not spawnRange.has_value()) {
        throw std::runtime_error("Spawn range was not provided.");
    }

    return {
        std::move(cactus.value()),
        std::move(bird.value()),
        scale,
        spawnRange.value(),
        winWidth,
        cactusChance,
    };
}
