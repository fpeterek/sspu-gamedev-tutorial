//
// Created by fpeterek on 19.09.21.
//

#ifndef DINO_TEXT_HPP
#define DINO_TEXT_HPP

#include <SFML/Graphics.hpp>

class Text {

public:

    enum class Align {
        TopLeft, TopCenter, TopRight,
        CenterLeft, Center, CenterRight,
        BottomLeft, BottomCenter, BottomRight,
    };

private:

    sf::Text text;
    sf::Vector2f position;

public:

    Text(const sf::Font & font, sf::Vector2f position, const std::string & content = "");

};

#endif //DINO_TEXT_HPP
