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

	bool intersects(PhysicsComponent& pc, sf::RectangleShape& other);
	bool intersects(PhysicsComponent& pc, sf::CircleShape& other);


	const sf::Vector2f& getVelocity() const { return velocity; }

private:
	sf::Vector2f velocity;
};
