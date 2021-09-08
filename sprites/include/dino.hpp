//
// Created by fpeterek on 08.09.21.
//

#ifndef TMPL_PROJECT_DINO_HPP
#define TMPL_PROJECT_DINO_HPP

#include <vector>

#include <SFML/Graphics.hpp>

class Dino : public sf::Drawable {
    const std::vector<sf::Texture> & textures;
    sf::Sprite sprite;
    const float cyclePeriod;
    const float textureLifetime;
    float t = 0;
public:
    Dino(const std::vector<sf::Texture> & textures, float cyclePeriod);

    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scales);
    void setScale(float sx, float sy);

    float width() const;
    float height() const;
    sf::Vector2f size() const;

    void update(float dt);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};

#endif //TMPL_PROJECT_DINO_HPP
