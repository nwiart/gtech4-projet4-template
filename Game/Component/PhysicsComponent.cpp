#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
{

}

void PhysicsComponent::update(float dt)
{
    //gameobject.getposition() += velocity * dt;
}

void PhysicsComponent::setVelocity(sf::Vector2f& newVelocity)
{
    velocity = newVelocity;
}

bool PhysicsComponent::intersects(PhysicsComponent& pc, sf::RectangleShape& other)
{
    return pc.getShape().getGlobalBounds().intersects(other.getGlobalBounds());
}

sf::RectangleShape &PhysicsComponent::getShape()
{
    return shape;
}
