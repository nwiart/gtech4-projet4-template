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
