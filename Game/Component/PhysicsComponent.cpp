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
    return pc.getGlobalBounds().intersects(other.getGlobalBounds());
}

bool PhysicsComponent::intersects(PhysicsComponent& pc, sf::CircleShape& other)
{
    return false;
}
