//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_GAME_HPP
#define DINO_GAME_HPP

#include <vector>

#include "window.hpp"
#include "ground.hpp"
#include "texture_loader.hpp"
#include "enemy.hpp"
#include "dino.hpp"

class Game {

    static constexpr float defaultSpeed = -200;
    static constexpr float g = 700;
    static constexpr float jumpForce = -550;

    float speed = 1.0;
    TextureLoader tl;
    Window window;
    Ground ground;
    Enemy::Factory enemyFactory;
    std::vector<Enemy> enemies;
    Dino dino;

    std::default_random_engine rand;
    std::uniform_real_distribution<double> spawnDist;
    float untilSpawn = 0.0;

    void applyGravity(float dt);
    void update(float dt);
    void popEnemies();
    void createEnemy();

    void reset();
    void start();

public:
    Game();
    void play();

};

#endif //DINO_GAME_HPP
