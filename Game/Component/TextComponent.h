#pragma once
#include "IncludeSFML.h"
#include <iostream>

class TextComponent
{
public:

    typedef class TextSystem SystemType;

    inline sf::Text* getText() { return &text; }

    inline void setColor(sf::Color color) { return text.setFillColor(color); }
    inline void setCharacterSize(int size) { return text.setCharacterSize(size); }
    inline void setFont(sf::Font& font) { return text.setFont(font); }
    inline void setString(sf::String str) { return text.setString(str); }

private:
    sf::Text text;
};