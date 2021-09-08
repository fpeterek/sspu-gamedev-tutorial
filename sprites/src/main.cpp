#include <vector>
#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "dino.hpp"

sf::RenderWindow createWindow() {
    return {
        sf::VideoMode::getDesktopMode(),
        "Sprites",
        sf::Style::Fullscreen,
    };
}

bool closed(const sf::Event & ev) {
    return ev.type == sf::Event::Closed;
}

bool pressed(const sf::Event & ev, const sf::Keyboard::Key key) {
    return ev.type == sf::Event::KeyPressed and ev.key.code == key;
}

sf::Texture loadTexture(const std::string & path, const int begin = 0, const int width = 16) {
    sf::Texture tex;
    if (not tex.loadFromFile(path, { begin, 0, width, width })) {
        throw std::runtime_error("Texture " + path + " could not be loaded.");
    }
    tex.setRepeated(false);
    tex.setSmooth(false);
    return tex;
}

std::vector<sf::Sprite> createRectangles(const sf::Vector2u winDim, const sf::Texture & texture) {
    constexpr float rectWidth = 16 * 4;

    const size_t rectCount = std::ceil(winDim.x / rectWidth);
    const float rectY = std::roundf(winDim.y * 0.7);
    const float scale = rectWidth / texture.getSize().x;

    std::vector<sf::Sprite> rects;
    rects.reserve(rectCount);

    for (size_t i = 0; i < rectCount; ++i) {
        rects.emplace_back(texture);
        rects.back().setScale(scale, scale);
        rects.back().setPosition(i * rectWidth, rectY);
    }

    return rects;
}

int main(int argc, const char * argv[]) {
    sf::RenderWindow win = createWindow();
    const auto grassTexture = loadTexture("resources/grass.png");
    const auto grass = createRectangles(win.getSize(), grassTexture);
    std::vector<sf::Texture> dinoTextures;
    dinoTextures.emplace_back(loadTexture("resources/dino.png", 0, 16));
    dinoTextures.emplace_back(loadTexture("resources/dino.png", 16, 16));

    Dino dino { dinoTextures, 0.5 };
    dino.setScale(4, 4);
    dino.setPosition({ win.getSize().x/4.f, grass.front().getGlobalBounds().top - dino.height()/2 });

    sf::Clock clock;

    while (win.isOpen()) {

        sf::Event ev {};
        while (win.pollEvent(ev)) {
            if (closed(ev) or pressed(ev, sf::Keyboard::Q) or pressed(ev, sf::Keyboard::Escape)) {
                win.close();
            }
        }

        const float dt = clock.getElapsedTime().asSeconds();
        clock.restart();
        dino.update(dt);

        win.clear(sf::Color(99, 154, 242));
        win.draw(dino);
        for (const auto & tile : grass) {
            win.draw(tile);
        }
        win.display();
    }
}









