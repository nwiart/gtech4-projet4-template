#pragma once
#include "IncludeSFML.h"


class PhysicsComponent
{
public:

	PhysicsComponent();

	void update(float dt);

	void setVelocity(sf::Vector2f& newVelocity);
	bool intersects(PhysicsComponent& pc, sf::RectangleShape& other);

	sf::RectangleShape& getShape();

	const sf::Vector2f& getVelocity() const { return velocity; }

private:
	sf::Vector2f velocity;
	sf::RectangleShape shape;
};
