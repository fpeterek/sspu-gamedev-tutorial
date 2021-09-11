//
// Created by fpeterek on 11.09.21.
//

#include "game.hpp"

Game::Game() :
    tl {},
    window(1920, 1080),
    ground {
        tl.load("resources/sand.png"),
        tl[T("resources/sand.png")],
        { 1920, 256 },
        4.f
    } {
    window.setBackground(sf::Color(105, 157, 240));
    ground.setLevel(1080-256);
}

void Game::play() {
    sf::Clock clock;
    while (window.isOpen()) {
        window.handleEvents();

        const double dt = clock.restart().asSeconds();
        ground.move(dt * speed * -100);

        window.redraw(ground);
    }
}

