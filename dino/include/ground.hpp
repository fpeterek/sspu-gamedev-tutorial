//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_GROUND_HPP
#define DINO_GROUND_HPP

#include <SFML/Graphics.hpp>

class Ground : public sf::Drawable {

    mutable sf::Sprite top;
    mutable sf::Sprite bottom;
    const float scale;
    const sf::Vector2i dim;
    const sf::Vector2i tileDim;

    sf::Vector2f pos;

    void drawLine(sf::RenderTarget & tg, sf::RenderStates st, sf::Sprite & sprite, float y) const;

public:

    void setPosition(sf::Vector2f position);
    void setLevel(float y);
    void move(float dx);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    Ground(const sf::Texture & top, const sf::Texture & bottom, sf::Vector2i dim, float scale);

};

#endif //DINO_GROUND_HPP
