#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


bool closed(const sf::Event & ev) {
    return ev.type == sf::Event::Closed;
}

bool pressed(const sf::Event & ev, const sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}


int main(int argc, const char * argv[]) {
    sf::RenderWindow win {
            sf::VideoMode(800, 600),
            "My Window",
            sf::Style::Titlebar | sf::Style::Close
    };
    sf::RectangleShape rect({100, 100});
    rect.setFillColor(sf::Color::Magenta);
    rect.setOrigin(50, 50);
    rect.setPosition(400, 300);

    while (win.isOpen()) {

        sf::Event ev {};
        while (win.pollEvent(ev)) {
            if (closed(ev) or pressed(ev, sf::Keyboard::Q) or pressed(ev, sf::Keyboard::Escape)) {
                win.close();
            }
        }

        win.clear(sf::Color::White);
        win.draw(rect);
        win.display();
    }
}
