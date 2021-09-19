//
// Created by fpeterek on 19.09.21.
//

#include <text.hpp>

Text::Text(const sf::Font & font, const sf::Vector2f pos, const std::string & content) {
    text.setFont(font);
    position = pos;
    text.setString(sf::String(content));
}

