#pragma once
#include "IncludeSFML.h"

class RectComponent
{
public:
    typedef class RectSystem SystemType;

    sf::Shape *getShape() { return &m_shape; }

    inline void setColor(sf::Color color) { m_shape.setFillColor(color); }
    inline void setSize(sf::Vector2f size) { m_shape.setSize(size); }
    inline void setTexture(sf::Texture &text) { m_shape.setTexture(&text); }

    inline float getSizeX() const { return m_shape.getSize().x; }
    inline float getSizeY() const { return m_shape.getSize().y; }

private:
    sf::RectangleShape m_shape;
};