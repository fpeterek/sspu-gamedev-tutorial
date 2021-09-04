#include <vector>
#include <cmath>
#include <random>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

sf::RenderWindow initWindow() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    return {
        sf::VideoMode::getDesktopMode(),
        "Mouse Input",
        sf::Style::Fullscreen,
        settings,
    };
}

bool isClosed(const sf::Event & ev) {
    return ev.type == sf::Event::Closed;
}

bool isKey(const sf::Event & ev, const sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}

bool isMouseDown(const sf::Event & ev, const sf::Mouse::Button button) {
    return ev.type == sf::Event::MouseButtonPressed and ev.mouseButton.button == button;
}

bool isMouseUp(const sf::Event & ev, const sf::Mouse::Button button) {
    return ev.type == sf::Event::MouseButtonReleased and ev.mouseButton.button == button;
}

bool isScrollUp(const sf::Event & ev) {
    return ev.type == sf::Event::MouseWheelScrolled and ev.mouseWheelScroll.delta > 0;
}

bool isScrollDown(const sf::Event & ev) {
    return ev.type == sf::Event::MouseWheelScrolled and ev.mouseWheelScroll.delta < 0;
}

sf::CircleShape createCircle(sf::Vector2f center) {
    sf::CircleShape circle(1);
    circle.setOrigin(1, 1);
    circle.setPosition(center);
    circle.setFillColor({ 52, 132, 168 });
    return circle;
}

sf::Vector2f getMousePos(const sf::RenderWindow & win) {
    const auto pos = sf::Mouse::getPosition(win);
    return { (float)pos.x, (float)pos.y };
}

float calcLength(const sf::Vector2f p1, const sf::Vector2f p2) {
    const auto dx = p1.x - p2.x;
    const auto dy = p1.y - p2.y;
    return std::sqrt(dx*dx + dy*dy);
}

sf::Color randColor() {
    static std::default_random_engine gen(time(nullptr));
    static std::uniform_int_distribution<uint8_t> dist(0, 255);
    return { dist(gen), dist(gen), dist(gen) };
}

int main(int argc, const char * argv[]) {
    auto win = initWindow();
    win.setKeyRepeatEnabled(false);

    std::vector<sf::CircleShape> circles;
    size_t current = -1;

    while (win.isOpen()) {

        sf::Event ev {};
        while (win.pollEvent(ev)) {
            if (isClosed(ev) or isKey(ev, sf::Keyboard::Q) or isKey(ev, sf::Keyboard::Escape)) {
                win.close();
            } else if (isMouseDown(ev, sf::Mouse::Left)) {
                circles.emplace_back(createCircle({ (float)ev.mouseButton.x, (float)ev.mouseButton.y }));
                current = circles.size()-1;
            } else if (isMouseUp(ev, sf::Mouse::Left)) {
                current = -1;
            } else if (isScrollUp(ev) and current != -1ull) {
                circles[current].setPointCount(circles[current].getPointCount()+1);
            } else if (isScrollDown(ev) and current != -1ull) {
                circles[current].setPointCount(std::max(3ul, circles[current].getPointCount()-1));
            } else if (isKey(ev, sf::Keyboard::Space)) {
                circles[current].setFillColor(randColor());
            }
        }

        if (current != -1ull) {
            const auto mousePos = getMousePos(win);
            const auto center = circles[current].getPosition();
            const auto radius = calcLength(mousePos, center);
            circles[current].setOrigin(radius, radius);
            circles[current].setRadius(radius);
        }

        win.clear(sf::Color::White);
        for (const auto & c : circles) {
            win.draw(c);
        }
        win.display();
    }
}
