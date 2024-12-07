#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics/Text.hpp>
class FontDictionary {
	static std::unordered_map<std::string, sf::Font> fontMap;
public:

	static void RegisterFont(const std::string name, sf::Font fnt) {
		if (fontMap.find(name) == fontMap.end()) {
			fontMap.emplace(fnt);
		}
	}
	static sf::Font& GetFont(const std::string& fontName) {
		if (fontMap.find(fontName) != fontMap.end())
		{
			return fontMap[fontName];
		}
	}
};