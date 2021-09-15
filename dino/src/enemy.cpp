//
// Created by fpeterek on 11.09.21.
//

#include <enemy.hpp>
#include <utility>

Enemy::Factory::Factory(
    TextureCycler cactus, TextureCycler bird, const float scale, const decltype(yRange) yRange, const uint winWidth) :
    cactus(std::move(cactus)), bird(std::move(bird)), scale(scale), yRange(yRange), windowWidth(winWidth),
    rand(time(nullptr)) { }

Enemy Enemy::Factory::create() {
    if (std::uniform_int_distribution(1, 3)(rand) == 3) {
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
        sprite.getPosition().x + (sprite.getLocalBounds().width - hitboxSize.x) / 2,
        sprite.getPosition().y + (sprite.getLocalBounds().height - hitboxSize.y) / 2,
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
