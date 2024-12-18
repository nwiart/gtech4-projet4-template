#pragma once
#include "IncludeSFML.h"

class CircleComponent
{
public:

    typedef class CircleSystem SystemType;

    sf::Shape* getShape() { return &m_shape; }

private:
    sf::CircleShape m_shape;
};