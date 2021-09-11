//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_GAME_HPP
#define DINO_GAME_HPP

#include "window.hpp"
#include "ground.hpp"
#include "texture_loader.hpp"

class Game {

    float speed = 1.0;
    TextureLoader tl;
    Window window;
    Ground ground;

    void reset();
    void start();

public:
    Game();
    void play();
};

#endif //DINO_GAME_HPP
