#include "GameManager.h"
#include "PhysicsSystem.h"
#include "Scene/GameObject.h"

#include <vector>

PhysicsSystem::PhysicsSystem()
{
}

PhysicsComponent *PhysicsSystem::add(GameObject &obj)
{
	auto p = m_components.emplace(obj, PhysicsComponent{});
	PhysicsComponent &c = p.first->second;
	return &c;
}

void PhysicsSystem::remove(GameObject &obj)
{
	m_components.erase(obj);
}

void PhysicsSystem::update(float dt)
{
	std::vector<PhysicsComponent *> allComponents;
	allComponents.reserve(m_components.size());

	// Integrate.
	for (auto &[id, component] : m_components)
	{
		GameObject *obj = GameManager::getInstance().getObjectByID(id);
		obj->setPosition(obj->getPosition() + component.velocity * dt);

		allComponents.push_back(&component);
	}

	// Collision test.
	for (int i = 0; i < allComponents.size(); i++)
	{
		for (int j = i + 1; j < allComponents.size(); j++)
		{
		}
	}
	for (auto &[id, component] : m_components)
	{
		GameObject *obj = GameManager::getInstance().getObjectByID(id);

		// RectComponent& rect = obj->getComponent<RectComponent>();
	}
}

PhysicsComponent &PhysicsSystem::get(GameObject &obj)
{
	if (auto it = m_components.find(obj); it != m_components.end())
	{
		return it->second;
	}
}
