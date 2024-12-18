#pragma once
#include "IncludeSFML.h"

class CircleComponent
{
public:

    typedef class CircleSystem SystemType;

    sf::Shape* getShape() { return &m_shape; }

    inline void setColor(sf::Color color) { m_shape.setFillColor(color); }
    inline void setRadius(int radius) { m_shape.setRadius(radius); }
    inline void setTexture(sf::Texture(text)) { m_shape.setTexture(&text); }
private:
    sf::CircleShape m_shape;
};