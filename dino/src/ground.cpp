//
// Created by fpeterek on 11.09.21.
//

#include "ground.hpp"

#include <cmath>

#include "util.hpp"

static sf::Vector2i calcDim(const sf::Vector2u texDim, const float scale) {
    return { int(texDim.x * scale), int(texDim.y * scale) };
}

Ground::Ground(const sf::Texture & surfTex, const sf::Texture & dirtTex, sf::Vector2i dim, float scale) :
    surface(surfTex), dirt(dirtTex), dim(dim), tileDim(calcDim(surfTex.getSize(), scale)) {
    surface.setScale(scale, scale);
    dirt.setScale(scale, scale);
}

void Ground::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    drawLine(target, states, surface, pos.y);
    for (int64_t yOffset = tileDim.y; yOffset < dim.y; yOffset += tileDim.y) {
        drawLine(target, states, dirt, pos.y + (float)yOffset);
    }
}

void Ground::drawLine(sf::RenderTarget & tg, sf::RenderStates st, sf::Sprite & sprite, const float y) const {
    for (float begin = pos.x; begin <= (float)dim.x; begin += tileDim.x) {
        sprite.setPosition(begin, y);
        tg.draw(sprite, st);
    }
}

void Ground::move(const float dx) {
    pos.x = std::fmod(pos.x + dx, (float)tileDim.x);
}

void Ground::setPosition(const sf::Vector2f position) {
    pos = position;
}

void Ground::setLevel(const float y) {
    pos.y = y;
}

