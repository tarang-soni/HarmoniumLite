#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>

const float PI = 3.14159265358979323846f;
inline  sf::Color hexToColor(const std::string& hex) {
    if (hex.size() != 7 || hex[0] != '#') {
        throw std::invalid_argument("Invalid color format. Expected format: #RRGGBB");
    }

    // Extract the hex components
    unsigned int r, g, b;
    std::istringstream(hex.substr(1, 2)) >> std::hex >> r;
    std::istringstream(hex.substr(3, 2)) >> std::hex >> g;
    std::istringstream(hex.substr(5, 2)) >> std::hex >> b;

    return sf::Color(r, g, b);
}