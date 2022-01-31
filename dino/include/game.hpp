//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_GAME_HPP
#define DINO_GAME_HPP

#include <vector>

#include "window.hpp"
#include "ground.hpp"
#include "textures.hpp"
#include "enemy.hpp"
#include "dino.hpp"
#include "text.hpp"
#include "sky.hpp"

class Game {

    static constexpr float defaultSpeed = -200;
    static constexpr float g = 700;
    static constexpr float jumpForce = -550;
    static constexpr float distanceMod = 15;

    bool alive = true;
    float speed = 1.0;
    float distance = 0;
    TextureLoader tl;
    sf::Shader skyShader;
    sf::Shader shader;
    Window window;
    Ground ground;
    Sky sky;
    Enemy::Factory enemyFactory;
    std::vector<Enemy> enemies;
    Dino dino;

    std::default_random_engine rand;
    std::uniform_real_distribution<double> spawnDist;
    float untilSpawn = 0.0;

    Text distanceText;
    Text gameOverText;

    void die();
    void applyGravity(float dt);
    void update(float dt);
    void updateDistText();
    void checkCollisions();
    void popEnemies();
    void createEnemy();

    void reset();

public:
    Game();
    void play();

};

#endif //DINO_GAME_HPP
