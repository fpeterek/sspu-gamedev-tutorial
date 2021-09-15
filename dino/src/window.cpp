//
// Created by fpeterek on 11.09.21.
//

#include "window.hpp"

void Window::intRedraw() {
    win.display();
}

void Window::setBackground(const sf::Color color) {
    background = color;
}

void Window::draw(const sf::Drawable & drawable) {
    win.draw(drawable);
}

Window::Window(const uint width, const uint height) :
    win {
        { width, height },
        "Dino",
        sf::Style::Fullscreen,
    } { }

void Window::handleEvents() {
    sf::Event ev {};
    while (win.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed or (ev.type == sf::Event::KeyPressed and ev.key.code == sf::Keyboard::Escape)) {
            close();
        }
    }
}

void Window::close() {
    win.close();
}

bool Window::isOpen() {
    return win.isOpen();
}

sf::Vector2u Window::size() const {
    return win.getSize();
}

uint Window::width() const {
    return size().x;
}

uint Window::height() const {
    return size().y;
}
