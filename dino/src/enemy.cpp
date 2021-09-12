//
// Created by fpeterek on 11.09.21.
//

#include <enemy.hpp>

Enemy::Factory::Factory(
    TextureCycler cactus, TextureCycler bird, const float scale, const decltype(yRange) yRange, const uint winWidth) :
    cactus(std::move(cactus)), bird(std::move(bird)), scale(scale), yRange(yRange), windowWidth(winWidth) {



}

