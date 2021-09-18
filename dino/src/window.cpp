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

void Window::processKeyboard() {
    for (auto & pair : keyPress) {
        if (sf::Keyboard::isKeyPressed(pair.first)) {
            pair.second();
        }
    }
}

void Window::pollEvents() {
    sf::Event ev {};
    while (win.pollEvent(ev)) {
        const auto iter = events.find(ev.type);
        if (iter == events.end()) {
            continue;
        }
        iter->second(ev);
    }
}

void Window::handleEvents() {
    pollEvents();
    processKeyboard();
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

void Window::setCallback(const sf::Keyboard::Key key, KeyCallback callback) {
    keyPress[key] = std::move(callback);
}

void Window::setCallback(const sf::Event::EventType key, EventCallback callback) {
    events[key] = std::move(callback);
}

