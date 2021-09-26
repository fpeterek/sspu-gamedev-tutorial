//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_DINO_HPP
#define DINO_DINO_HPP

#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "textures.hpp"


class Dino : public sf::Drawable {

    TextureCycler runTexture;
    TextureCycler jumpTexture;
    std::reference_wrapper<TextureCycler> current;
    sf::Sprite sprite;
    sf::Vector2f force;
    sf::Vector2f position;

    bool canJump = false;

    void updateSprite();

public:

    Dino(TextureCycler run, TextureCycler jump, sf::Vector2f position, float scale);
    ~Dino() override = default;

    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    void move(sf::Vector2f delta);
    void applyForce(sf::Vector2f force);
    void setPosition(sf::Vector2f position);
    void setY(float y);
    void update(float dt);
    void jump(float force);
    void land();

    sf::Vector2f getForce() const;
    sf::FloatRect hitbox() const;

};


#endif //DINO_DINO_HPP
