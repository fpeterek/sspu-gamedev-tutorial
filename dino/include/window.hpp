//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_WINDOW_HPP
#define DINO_WINDOW_HPP

#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Window {

public:
    typedef std::function<void(void)> KeyCallback;
    typedef std::function<void(const sf::Event&)> EventCallback;

private:

    sf::RenderWindow win;
    sf::Color background;

    std::unordered_map<sf::Keyboard::Key, KeyCallback> keyPress;
    std::unordered_map<sf::Event::EventType, EventCallback> events;

    template<typename Drawable, typename... Rest>
    void intRedraw(const Drawable & drawable, const Rest &... rest);

    template<typename Drawable>
    void intRedraw(const Drawable & drawable);

    void intRedraw();

    void draw(const sf::Drawable & drawable);

    template<template<typename> typename collection, typename T>
    void draw(const collection<T> & drawables);

    void processKeyboard();
    void pollEvents();

public:

    Window(uint width, uint height);

    void setBackground(sf::Color color);

    void setCallback(sf::Event::EventType, EventCallback callback);
    void setCallback(sf::Keyboard::Key, KeyCallback callback);

    void handleEvents();
    bool isOpen();
    void close();

    sf::Vector2u size() const;
    uint width() const;
    uint height() const;

    template<typename... Drawable>
    void redraw(const Drawable &...);

};

template<template<typename> typename collection, typename T>
void Window::draw(const collection<T> & drawables) {
    for (const T & d : drawables) {
        draw(d);
    }
}

template<typename... Drawable>
void Window::redraw(const Drawable &... drawables) {
    win.clear(background);
    intRedraw(drawables...);
}

template<typename Drawable, typename... Rest>
void Window::intRedraw(const Drawable & drawable, const Rest &... rest) {
    draw(drawable);
    intRedraw(rest...);
}

template<typename Drawable>
void Window::intRedraw(const Drawable & drawable) {
    win.draw(drawable);
    intRedraw();
}

#endif //DINO_WINDOW_HPP
