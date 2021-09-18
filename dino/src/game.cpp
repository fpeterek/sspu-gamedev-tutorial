//
// Created by fpeterek on 11.09.21.
//

#include "game.hpp"

#include <cmath>

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
    dino {
        { tl.loadSheet("resources/dino.png", { 16, 16 }, "dinoRun"), 0.5 },
        { tl.loadSheet("resources/dino.png", { 16, 16 }, "dinoJump", 1), 1.0 },
        { 300, 540 },
        4.f
    },
    rand(time(nullptr)),
    spawnDist(2, 4) {

    window.setBackground(sf::Color(105, 157, 240));
    ground.setLevel(1080-256);

    window.setCallback(sf::Keyboard::Space, [this]() -> void { dino.jump(jumpForce); });
    window.setCallback(sf::Keyboard::Escape, [this]() -> void { window.close(); });
    window.setCallback(sf::Keyboard::Q, [this]() -> void { window.close(); });

    window.setCallback(sf::Event::Closed, [this](const sf::Event&) -> void { window.close(); });
}

void Game::play() {
    sf::Clock clock;
    while (window.isOpen()) {
        window.handleEvents();

        const float dt = std::min(clock.restart().asSeconds() * speed, 0.1f);

        update(dt);
        popEnemies();
        createEnemy();

        window.redraw(ground, enemies, dino);
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
    dino.update(dt);
    applyGravity(dt);
}

void Game::applyGravity(const float dt) {
    dino.applyForce({ 0.f, dt * g });
    const auto current = dino.getForce();
    const sf::Vector2f delta = { current.x * dt, current.y * dt };
    dino.move(delta);
    const auto top = dino.getHitbox().top;
    const auto bottom = top + dino.getHitbox().height;
    if (bottom >= ground.level()) {
        dino.land();
        dino.setY(top - (bottom-ground.level()));
    }
}

