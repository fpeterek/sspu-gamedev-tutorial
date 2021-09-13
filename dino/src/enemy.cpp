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

// TODO: Fix position
Enemy Enemy::Factory::createBird() {
    return Enemy(bird, scale, { (float)windowWidth, (float)yRange.first }, { 14.f, 6.f });
}

Enemy Enemy::Factory::createCactus() {
    return Enemy(cactus, scale, { (float)windowWidth, (float)yRange.second }, { 10.f, 14.f });
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
