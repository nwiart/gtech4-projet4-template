#pragma once
#include "IncludeSFML.h"

class PhysicsComponent
{
	friend class PhysicsSystem;

public:

	typedef class PhysicsSystem SystemType;


	PhysicsComponent();

	void update(float dt);

	void setVelocity(sf::Vector2f& newVelocity);


	const sf::Vector2f& getVelocity() const { return velocity; }

private:
	sf::Vector2f velocity;
};
