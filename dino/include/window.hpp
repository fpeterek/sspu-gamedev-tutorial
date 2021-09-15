//
// Created by fpeterek on 11.09.21.
//

#ifndef DINO_WINDOW_HPP
#define DINO_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Window {

    sf::RenderWindow win;
    sf::Color background;

    template<typename Drawable, typename... Rest>
    void intRedraw(const Drawable & drawable, const Rest &... rest);

    template<typename Drawable>
    void intRedraw(const Drawable & drawable);

    void intRedraw();

    void draw(const sf::Drawable & drawable);

    template<typename collection>
    void draw(const collection & drawables);

public:

    Window(uint width, uint height);

    void setBackground(sf::Color color);

    void handleEvents();
    bool isOpen();
    void close();

    sf::Vector2u size() const;
    uint width() const;
    uint height() const;

    template<typename... Drawable>
    void redraw(const Drawable &...);

};

template<typename collection>
void Window::draw(const collection & drawables) {
    for (const sf::Drawable & d : drawables) {
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
