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

class Text : public sf::Drawable {

public:

    enum class Align {
        TopLeft, TopCenter, TopRight,
        CenterLeft, Center, CenterRight,
        BottomLeft, BottomCenter, BottomRight,
    };

private:

    sf::Text text;
    Align alignment = Align::TopLeft;
    float scale = 1.0;
    uint size = 12;
    float outlineThickness = 0;
    bool hidden = false;
    void adjustPosition();
    void adjustSize();

protected:
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

public:

    void show();
    void hide();
    void setString(const sf::String & str);
    void setPosition(sf::Vector2f position);
    void setFillColor(sf::Color color);
    void setOutlineColor(sf::Color color);
    void setOutlineThickness(float thickness);
    void setCharacterSize(uint size);
    void setScale(float scale);
    void align(Align alignment);

    Text(const sf::Font & font, sf::Vector2f position, const std::string & content = "", uint size = 12);
    ~Text() override = default;
};

#endif //DINO_TEXT_HPP
