//
// Created by fpeterek on 19.09.21.
//

#ifndef DINO_TEXT_HPP
#define DINO_TEXT_HPP

#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

class FontLoader {

    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;

    static FontLoader * fl;

    FontLoader() noexcept = default;

public:

    static FontLoader & instance();

    const sf::Font & loadFont(const std::string & font, const std::string & key = "");
    const sf::Font & get(const std::string & font) const;
    const sf::Font & operator[](const std::string & font) const;

    void pop(const std::string & font);
};

// TODO: sf::Text is not meant to be inherited from
class Text : public sf::Text {

public:

    enum class Align {
        TopLeft, TopCenter, TopRight,
        CenterLeft, Center, CenterRight,
        BottomLeft, BottomCenter, BottomRight,
    };

private:

    Align alignment = Align::TopLeft;
    void adjustPosition();

public:

    void setString(const sf::String & str);
    void setPosition(sf::Vector2f position);
    void setCharacterSize(uint size);
    void align(Align alignment);

public:

    Text(const sf::Font & font, sf::Vector2f position, const std::string & content = "", uint size = 12);
};

#endif //DINO_TEXT_HPP
