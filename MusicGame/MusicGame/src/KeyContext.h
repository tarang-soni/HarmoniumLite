#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include "Scales.h"
struct KeyContext {
    const sf::RenderWindow& windowRef;
    const int& currentOctaveRef;
    std::unordered_map<int, std::unordered_map <Scales, sf::SoundBuffer>>& bufferRef;
    std::unordered_map<sf::Keyboard::Key, sf::Sound>& keysRef;

    KeyContext(const sf::RenderWindow& window, const int& currentOctave, std::unordered_map<int, std::unordered_map <Scales, sf::SoundBuffer>>& buffers,  std::unordered_map<sf::Keyboard::Key, sf::Sound>& keys)
        :windowRef(window),
        currentOctaveRef(currentOctave),
        bufferRef(buffers),
        keysRef(keys) {}
};