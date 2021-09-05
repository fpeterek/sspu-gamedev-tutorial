#include <vector>
#include <cmath>
#include <functional>

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

sf::CircleShape createCircle(const sf::Vector2f pos) {
    sf::CircleShape circle(50);
    circle.setOrigin(50, 50);
    circle.setOutlineThickness(3);
    circle.setPosition(pos);
    return circle;
}

std::vector<sf::RectangleShape> createRectangles() {
    return {
        createRect({ 300, 370 }, 45),
        createRect({ 1500, 600 }, 23),
        createRect({ 680, 850}, 11),
        createRect({ 940, 500}, 37),
    };
}

std::vector<sf::CircleShape> createCircles() {
    return {
        createCircle({ 1230, 240 }),
        createCircle({ 330, 720 }),
        createCircle({ 1640, 830 }),
    };
}

template<typename DestClass, typename OrigClass>
void addAsReferences(std::vector<std::reference_wrapper<DestClass>> & dest, std::vector<OrigClass> & coll) {
    for (auto & item : coll) {
        dest.template emplace_back(item);
    }
}

auto createShapes() {
    return std::make_pair(createRectangles(), createCircles());
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

bool inside(const sf::RectangleShape & rect, const sf::Vector2f mouse) {

    auto copy = rect;
    const auto mouseDist = calcDist(copy.getPosition(), mouse);
    const auto rotation = ((360-rect.getRotation()) / (180 / M_PI));
    const auto mouseAngle = calcAngle(rect.getPosition(), mouse);
    const auto realAngle = mouseAngle + rotation;
    const sf::Vector2f realMouse {
        copy.getPosition().x + (float)std::cos(realAngle)*mouseDist,
        copy.getPosition().y + (float)std::sin(realAngle)*mouseDist,
    };

    copy.setRotation(0);
    return copy.getGlobalBounds().contains(realMouse);
}

bool inside(const sf::CircleShape & circle, const sf::Vector2f mouse) {
    const auto dist = calcDist(circle.getPosition(), mouse);
    return dist <= circle.getRadius();
}

void resetColors(std::vector<std::reference_wrapper<sf::Shape>> & shapes) {
    for (auto & shape : shapes) {
        shape.get().setFillColor(colors::defaultFill);
        shape.get().setOutlineColor(colors::defaultOutline);
    }
}

template<typename Shape>
void colorOnHover(std::vector<Shape> & shapes, const sf::Vector2i mouse) {
    const auto fmouse = sf::Vector2f(mouse.x, mouse.y);
    for (auto & shape : shapes) {
        if (inside(shape, fmouse)) {
            shape.setFillColor(colors::specialFill);
            shape.setOutlineColor(colors::specialOutline);
        }
    }
}

void handleEvents(sf::RenderWindow & win) {
    sf::Event ev {};
    while (win.pollEvent(ev)) {
        if (closed(ev) or pressed(ev, sf::Keyboard::Q) or pressed(ev, sf::Keyboard::Escape)) {
            win.close();
        }
    }
}

void redraw(sf::RenderWindow & win, const std::vector<std::reference_wrapper<sf::Shape>> & shapes) {
    win.clear(sf::Color::White);
    for (const auto & shape : shapes) {
        win.draw(shape);
    }
    win.display();
}

int main(int argc, const char * argv[]) {
    auto win = initWindow();

    auto [rectangles, circles] = createShapes();
    std::vector<std::reference_wrapper<sf::Shape>> shapes;
    shapes.reserve(rectangles.size() + circles.size());
    addAsReferences(shapes, rectangles);
    addAsReferences(shapes, circles);

    while (win.isOpen()) {
        resetColors(shapes);
        handleEvents(win);

        const auto mouse = sf::Mouse::getPosition(win);
        colorOnHover(rectangles, mouse);
        colorOnHover(circles, mouse);

        redraw(win, shapes);
    }
}
