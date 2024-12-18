#pragma once
#include "IncludeSFML.h"

class RenderComponent
{
public:

	typedef class RenderSystem SystemType;


	RenderComponent() { }
	void draw(sf::RenderWindow& wd) const;

};
