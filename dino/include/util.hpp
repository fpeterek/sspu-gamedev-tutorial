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

#endif //TMPL_PROJECT_UTIL_HPP
