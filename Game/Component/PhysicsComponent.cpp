#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
    : m_onCollideScreenCallback(0), m_onCollideObjectCallback(0)
{

}

void PhysicsComponent::update(float dt)
{
    //gameobject.getposition() += velocity * dt;
}

void PhysicsComponent::setVelocity(const sf::Vector2f& newVelocity)
{
    velocity = newVelocity;
}
