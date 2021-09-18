//
// Created by fpeterek on 11.09.21.
//

#include "dino.hpp"

Dino::Dino(TextureCycler run, TextureCycler jump, const sf::Vector2f position, const float scale) :
    runTexture(std::move(run)), jumpTexture(std::move(jump)), current(runTexture), position(position) {

    sprite.setTexture(runTexture.current());
    sprite.setScale(scale, scale);
    updateSprite();
}

void Dino::move(const sf::Vector2f delta) {
    position.x += delta.x;
    position.y += delta.y;
    updateSprite();
}

void Dino::applyForce(const sf::Vector2f delta) {
    force.x += delta.x;
    force.y += delta.y;
}

void Dino::setPosition(const sf::Vector2f newPos) {
    position = newPos;
    updateSprite();
}

void Dino::updateSprite() {
    sprite.setPosition(position);
    sprite.setTexture(current.get().current());
}

void Dino::update(float dt) {
    current.get().update(dt);
    updateSprite();
}

void Dino::jump(const float fy) {
    if (canJump) {
        applyForce({ 0.f, fy });
        canJump = false;
        current = jumpTexture;
    }
}

void Dino::land() {
    applyForce({ 0.f, -force.y });
    canJump = true;
    current = runTexture;
}

sf::Vector2f Dino::getForce() const {
    return force;
}

sf::FloatRect Dino::getHitbox() const {
    return sprite.getGlobalBounds();
}

void Dino::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Dino::setY(const float y) {
    position.y = y;
    updateSprite();
}

