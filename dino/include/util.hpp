//
// Created by fpeterek on 02.09.21.
//

#ifndef TMPL_PROJECT_UTIL_HPP
#define TMPL_PROJECT_UTIL_HPP

#include <ostream>

#include <SFML/System.hpp>

template<typename T>
std::ostream & operator<<(std::ostream & os, sf::Vector2<T> vec) {
    return os << "Vector(x: " << vec.x << ", y: " << vec.y << ")";
}

template<typename T>
std::ostream & operator<<(std::ostream & os, sf::Vector3<T> vec) {
    return os << "Vector(x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ")";
}

template<typename T>
sf::Vector2<T> operator*(const sf::Vector2<T> vec, const T scalar) {
    return { vec.x * scalar, vec.y * scalar };
}

template<typename T>
sf::Vector3<T> operator*(const sf::Vector3<T> vec, const T scalar) {
    return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

template<typename T1, typename T2>
sf::Vector2<T2> operator*(const sf::Vector2<T1> vec, const T2 scalar) {
    return { vec.x * scalar, vec.y * scalar };
}

template<typename T1, typename T2>
sf::Vector3<T1> operator*(const sf::Vector3<T1> vec, const T2 scalar) {
    return { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

#endif //TMPL_PROJECT_UTIL_HPP
