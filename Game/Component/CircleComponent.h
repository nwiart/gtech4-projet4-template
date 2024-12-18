#pragma once
#include "IncludeSFML.h"

class CircleComponent
{
public:

    typedef class CircleSystem SystemType;

    sf::Shape* getShape() { return &m_shape; }

    inline void setColor(sf::Color color) { m_shape.setFillColor(color); }
    inline void setRadius(int radius) { m_shape.setRadius(radius); }
    inline void setTexture(sf::Texture& text) { m_shape.setTexture(&text); }

    inline float getRadius() const { return m_shape.getRadius(); }
    inline float getDiameter() const { return m_shape.getRadius() * 2.0f; }

private:
    sf::CircleShape m_shape;
};