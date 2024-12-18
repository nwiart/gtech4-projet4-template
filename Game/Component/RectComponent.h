#pragma once
#include "IncludeSFML.h"

class RectComponent 
{
public:
    sf::Shape* getShape() { return &m_shape; }

private:
    sf::RectangleShape m_shape;
};