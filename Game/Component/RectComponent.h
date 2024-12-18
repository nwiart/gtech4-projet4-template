#pragma once
#include "IncludeSFML.h"

class RectComponent 
{
public:
    
    typedef class RectSystem SystemType;

    sf::Shape* getShape() { return &m_shape; }

private:
    sf::RectangleShape m_shape;
};