#include <vector>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace colors {
    const sf::Color defaultFill { 130, 178, 255 };
    const sf::Color defaultOutline { 50, 70, 194 };
    const sf::Color specialFill { 232, 121, 139 };
    const sf::Color specialOutline { 184, 68, 87 };
}

sf::ContextSettings createContext() {
    sf::ContextSettings context;
    context.antialiasingLevel = 8;
    return context;
}

sf::RenderWindow initWindow() {
    return {
        sf::VideoMode::getDesktopMode(),
        "Mouse Detection",
        sf::Style::Fullscreen,
        createContext(),
    };
}

bool closed(const sf::Event & ev) {
    return ev.type == sf::Event::Closed;
}

bool pressed(const sf::Event & ev, const sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}

sf::RectangleShape createRect(const sf::Vector2f pos, const float rotation = 0) {
    sf::RectangleShape rect({ 100, 100 });
    rect.setOrigin(50, 50);
    rect.setPosition(pos);
    rect.setOutlineThickness(3);
    rect.setRotation(rotation);
    return rect;
}

float calcDist(const sf::Vector2f p1, const sf::Vector2f p2) {
    const auto dx = p1.x - p2.x;
    const auto dy = p1.y - p2.y;
    return std::sqrt(dx*dx + dy*dy);
}

float calcAngle(const sf::Vector2f p1, const sf::Vector2f p2) {
    if (p1.x == p2.x) {
        if (p1.y == p2.y) {
            return 0;
        }
        if (p1.y < p2.y) {
            return M_PI * 1.5;
        }
        return M_PI_2;
    }
    if (p1.y == p2.y) {
        if (p1.x < p2.x) {
            return 0;
        }
        return M_PI;
    }

    const auto dist = calcDist(p1, p2);
    const auto cos = (p1.x - p2.x) / dist;
    const auto acos = std::acos(cos);
    return (p1.y > p2.y) ? acos : (2*M_PI - acos);
}

bool inside(const sf::RectangleShape & rect, const sf::Vector2i mouse) {

    auto copy = rect;
    const sf::Vector2f mf { (float)mouse.x, (float)mouse.y };
    const auto mouseDist = calcDist(copy.getPosition(), mf);
    const auto rotation = ((360-rect.getRotation()) / (180 / M_PI));
    const auto mouseAngle = calcAngle(rect.getPosition(), mf);
    const auto realAngle = mouseAngle + rotation;
    const sf::Vector2f realMouse {
        copy.getPosition().x + (float)std::cos(realAngle)*mouseDist,
        copy.getPosition().y + (float)std::sin(realAngle)*mouseDist,
    };

    copy.setRotation(0);
    return copy.getGlobalBounds().contains(realMouse);
}

int main(int argc, const char * argv[]) {
    auto win = initWindow();

    std::vector<sf::RectangleShape> rectangles {
        createRect({ 300, 370 }, 45),
        createRect({ 1500, 600 }, 23),
        createRect({ 680, 790}, 11),
    };

    while (win.isOpen()) {

        for (auto & rect : rectangles) {
            rect.setFillColor(colors::defaultFill);
            rect.setOutlineColor(colors::defaultOutline);
        }

        sf::Event ev {};
        while (win.pollEvent(ev)) {
            if (closed(ev) or pressed(ev, sf::Keyboard::Q) or pressed(ev, sf::Keyboard::Escape)) {
                win.close();
            }
        }

        const auto mouse = sf::Mouse::getPosition(win);
        for (auto & rect : rectangles) {
            if (inside(rect, mouse)) {
                rect.setFillColor(colors::specialFill);
                rect.setOutlineColor(colors::specialOutline);
            }
        }

        win.clear(sf::Color::White);
        for (const auto & rect : rectangles) {
            win.draw(rect);
        }
        win.display();
    }
}
