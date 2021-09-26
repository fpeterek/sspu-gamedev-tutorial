//
// Created by fpeterek on 09.09.21.
//

#ifndef DINO_TEXTURES_HPP
#define DINO_TEXTURES_HPP

#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>

struct T {
    explicit T(std::string key);
    const std::string key;
};

struct S {
    explicit S(std::string key);
    const std::string key;
};

class TextureLoader {

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::shared_ptr<std::vector<sf::Texture>>> sheets;

public:

    void popSheet(const std::string & sheet);
    const std::vector<sf::Texture> & loadSheet(const std::string & sheet, sf::Vector2u texSize, std::string key = "", uint texCount = -1);
    const std::vector<sf::Texture> & getSheet(const std::string & sheet) const;

    void pop(const std::string & texture);
    const sf::Texture & load(const std::string & texture, sf::IntRect area = sf::IntRect(), std::string key = "");
    const sf::Texture & get(const std::string & texture) const;

    const sf::Texture & operator[](const T & texture) const;
    const std::vector<sf::Texture> & operator[](const S & sheet) const;
};

class TextureCycler {
    std::reference_wrapper<const std::vector<sf::Texture>> textures;
    float period;
    float textureLifetime;
    float t = 0;

public:
    TextureCycler(const std::vector<sf::Texture> & textures, float period);
    TextureCycler(TextureCycler && rv) noexcept;
    TextureCycler & operator=(TextureCycler && rv) noexcept;
    TextureCycler(const TextureCycler & other);
    void update(float dt);
    const sf::Texture & current();
};

#endif //DINO_TEXTURES_HPP
