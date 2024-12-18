#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{

}

PhysicsComponent* PhysicsSystem::add(GameObject& obj)
{
	auto p = m_components.emplace(obj, PhysicsComponent{});
	PhysicsComponent& c = p.first->second;
	return &c;
}
