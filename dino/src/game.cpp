//
// Created by fpeterek on 11.09.21.
//

#include "game.hpp"

Game::Game() :
    tl {},
    window(1920, 1080),
    ground {
        tl.load("resources/sand.png"),
        tl.load("resources/dirt.png"),
        { 1920, 256 },
        4.f
    },
    enemyFactory {
        { tl.loadSheet("resources/cactus.png", { 16, 16 }), 1.0 },
        { tl.loadSheet("resources/bird.png", { 16, 8 }), 0.5 },
        4.f,
        { 1080 - 256 - 64 - 32*8 , 1080 - 256 },
        window.width(),
    },
    rand(time(nullptr)),
    spawnDist(2, 4) {
    window.setBackground(sf::Color(105, 157, 240));
    ground.setLevel(1080-256);
}

void Game::play() {
    sf::Clock clock;
    while (window.isOpen()) {
        window.handleEvents();

        const float dt = clock.restart().asSeconds() * speed;

        update(dt);
        popEnemies();
        createEnemy();

        window.redraw(enemies, ground);
    }
}

void Game::createEnemy() {
    if (untilSpawn > 0) {
        return;
    }
    enemies.push_back(enemyFactory.create());
    untilSpawn += spawnDist(rand);
}

void Game::popEnemies() {
    while (not enemies.empty()) {
        const auto & hitbox = enemies[0].hitbox();
        if (hitbox.left + hitbox.width >= 0) {
            break;
        }
        enemies.erase(enemies.begin());
    }
}

void Game::update(const float dt) {
    ground.move(dt * defaultSpeed);
    untilSpawn -= dt;
    for (auto & enemy : enemies) {
        enemy.update(dt);
        enemy.move({ dt * defaultSpeed, 0.f });
    }
}

