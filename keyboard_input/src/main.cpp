#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>


sf::RectangleShape defaultRect() {
    sf::RectangleShape rect({50, 50});
    rect.setOrigin(25, 25);
    return rect;
}

bool closed(const sf::Event & ev) {
    return ev.type == sf::Event::Closed;
}

bool keyPressed(const sf::Event & ev, const sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}

bool keyPressed(const sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

float signum(const float num) {
    if (num < 0) {
        return -1;
    } else if (num > 0) {
        return 1;
    }
    return 0;
}

sf::Vector2f adjust(sf::Vector2f vec) {
    constexpr float v = M_SQRT2 / 2.f;

    vec = { signum(vec.x), signum(vec.y) };

    if (vec.x and vec.y) {
        vec.x = v * (vec.x > 0 ? 1.f : -1);
        vec.y = v * (vec.y > 0 ? 1.f : -1);
    }

    return vec;
}

sf::Vector2f readDesiredMovement() {
    sf::Vector2f vec { 0, 0 };
    if (keyPressed(sf::Keyboard::Up)) {
        --vec.y;
    }
    if (keyPressed(sf::Keyboard::Down)) {
        ++vec.y;
    }
    if (keyPressed(sf::Keyboard::Left)) {
        --vec.x;
    }
    if (keyPressed(sf::Keyboard::Right)) {
        ++vec.x;
    }
    return vec;
}

sf::RenderWindow initWindow() {
    return {
        sf::VideoMode(1200, 800),
        "Keyboard Input",
        sf::Style::Close | sf::Style::Titlebar
    };
}

int main(int argc, const char * argv[]) {
    auto win = initWindow();

    sf::RectangleShape r1 = defaultRect();
    r1.setFillColor(sf::Color(121, 173, 237));
    r1.setPosition(900, 400);
    sf::Vector2f r1in { 0, 0 };

    sf::RectangleShape r2 = defaultRect();
    r2.setFillColor(sf::Color(237, 66, 115));
    r2.setPosition(300, 400);

    constexpr float velocity = 250.f;
    sf::Clock clock;
    auto begin = clock.getElapsedTime().asSeconds();

    while (win.isOpen()) {

        sf::Event ev {};
        while (win.pollEvent(ev)) {
            if (closed(ev) or keyPressed(ev, sf::Keyboard::Escape) or keyPressed(ev, sf::Keyboard::Q)) {
                win.close();
            }
            if (keyPressed(ev, sf::Keyboard::W)) {
                --r1in.y;
            } else if (keyPressed(ev, sf::Keyboard::S)) {
                ++r1in.y;
            } else if (keyPressed(ev, sf::Keyboard::A)) {
                --r1in.x;
            } else if (keyPressed(ev, sf::Keyboard::D)) {
                ++r1in.x;
            }
        }

        r1in = adjust(r1in);
        r1in = { r1in.x * 10, r1in.y * 10 };
        const auto r2in = adjust(readDesiredMovement());

        const auto now = clock.getElapsedTime().asSeconds();
        const auto dt = now - begin;
        begin = now;

        r1.move(r1in.x * velocity * dt, r1in.y * velocity * dt);
        r2.move(r2in.x * velocity * dt, r2in.y * velocity * dt);

        r1in = { 0, 0 };

        win.clear(sf::Color::White);
        win.draw(r1);
        win.draw(r2);
        win.display();
    }
}
