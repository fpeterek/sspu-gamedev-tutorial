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
    sky {
        { 1920, 1080-256 },
        4.f,
        tl.load("resources/cloud.png"),
    },
    enemyFactory(
        Enemy::Factory::Builder()
            .setCactusTexture({ tl.loadSheet("resources/cactus.png", { 16, 16 }), 1.0 })
            .setBirdTexture({ tl.loadSheet("resources/bird.png", { 16, 16 }), 0.5 })
            .setCactusChance(65)
            .setSpawnRange({ 1080 - 256 - 64 - 32*8 , 1080 - 256 })
            .setScale(4.f)
            .setWindowWidth(window.width())
            .create()
    ),
    dino {
        { tl.loadSheet("resources/dino.png", { 16, 16 }, "dinoRun"), 0.5 },
        { tl.loadSheet("resources/dino.png", { 16, 16 }, "dinoJump", 1), 1.0 },
        { 300, 540 },
        4.f
    },
    rand(time(nullptr)),
    spawnDist(2, 4),
    distanceText {
        FontLoader::instance().loadFont("resources/LCD_Solid.ttf"),
        { window.width()-5.f, 5.f }
    },
    gameOverText {
        FontLoader::instance()["resources/LCD_Solid.ttf"] ,
        { window.width() / 2.f, window.height() / 2.f },
        "Game Over"
    } {

    distanceText.setScale(4.f);
    distanceText.setCharacterSize(10);
    distanceText.setOutlineColor(sf::Color::Black);
    distanceText.setOutlineThickness(0.75);
    distanceText.align(Text::Align::TopRight);

    gameOverText.setScale(4.f);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(1);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setCharacterSize(18);
    gameOverText.align(Text::Align::Center);
    gameOverText.hide();

    window.setBackground(sf::Color(105, 157, 240));
    ground.setLevel(1080-256);

    window.setCallback(sf::Keyboard::Space, [this]() -> void { dino.jump(jumpForce); });
    window.setCallback(sf::Keyboard::Escape, [this]() -> void { window.close(); });
    window.setCallback(sf::Keyboard::Q, [this]() -> void { window.close(); });
    window.setCallback(sf::Keyboard::R, [this]() -> void { reset(); });

    window.setCallback(sf::Event::Closed, [this](const sf::Event&) -> void { window.close(); });
}

void Game::play() {
    sf::Clock clock;
    while (window.isOpen()) {
        window.handleEvents();

        const float dt = std::min(clock.restart().asSeconds() * speed, 0.1f) * alive;

        update(dt);
        checkCollisions();
        popEnemies();
        createEnemy();

        window.redraw(sky, ground, enemies, dino, distanceText, gameOverText);
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

void Game::updateDistText() {
    distanceText.setString(std::to_string((size_t)distance));
}

void Game::update(const float dt) {
    sky.update(dt);
    ground.move(dt * defaultSpeed);
    distance += std::abs(defaultSpeed * dt) / distanceMod;
    updateDistText();
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
    const auto top = dino.hitbox().top;
    const auto bottom = top + dino.hitbox().height;
    if (bottom >= ground.level()) {
        dino.land();
        dino.setY(top - (bottom-ground.level()));
    }
}

void Game::die() {
    alive = false;
    gameOverText.show();
}

void Game::checkCollisions() {
    const auto dinoHitbox = dino.hitbox();
    for (const auto & enemy : enemies) {
        if (enemy.hitbox().intersects(dinoHitbox)) {
            return die();
        }
    }
}

void Game::reset() {
    enemies.clear();
    gameOverText.hide();
    speed = 1.0;
    dino.setPosition({ 300.f, 540.f });
    dino.applyForce({ -dino.getForce().x, -dino.getForce().y });
    alive = true;
    distance = 0;
}

